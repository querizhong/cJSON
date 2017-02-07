/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unity/examples/unity_config.h"
#include "unity/src/unity.h"
#include "../cJSON.c"

static cJSON item[1];
const unsigned char *error_pointer = NULL;

static void assert_is_value(cJSON *value_item, int type)
{
    TEST_ASSERT_NOT_NULL_MESSAGE(value_item, "Item is NULL.");

    TEST_ASSERT_NULL_MESSAGE(value_item->next, "Linked list next pointer is not NULL.");
    TEST_ASSERT_NULL_MESSAGE(value_item->prev, "Linked list previous pointer is not NULL");
    TEST_ASSERT_BITS_MESSAGE(0xFF, type, value_item->type, "Message type is not number.");
    TEST_ASSERT_BITS_MESSAGE(cJSON_IsReference, 0, value_item->type, "Item should not have a string as reference.");
    TEST_ASSERT_BITS_MESSAGE(cJSON_StringIsConst, 0, value_item->type, "Item should not have a const string.");
    TEST_ASSERT_NULL_MESSAGE(value_item->string, "String is not NULL.");
}

static void assert_parse_value(const char *string, int type)
{
    TEST_ASSERT_NOT_NULL(parse_value(item, (const unsigned char*)string, &error_pointer));
    assert_is_value(item, type);
}

static void reset(void)
{
    if (item->child != NULL)
    {
        cJSON_Delete(item->child);
    }
    if (item->valuestring != NULL)
    {
        cJSON_free(item->valuestring);
    }
    memset(item, 0, sizeof(cJSON));
}

static void parse_value_should_parse_null(void)
{
    assert_parse_value("null", cJSON_NULL);
    reset();
}

static void parse_value_should_parse_true(void)
{
    assert_parse_value("true", cJSON_True);
    reset();
}

static void parse_value_should_parse_false(void)
{
    assert_parse_value("false", cJSON_False);
    reset();
}

static void parse_value_should_parse_number(void)
{
    assert_parse_value("1.5", cJSON_Number);
    reset();
}

static void parse_value_should_parse_string(void)
{
    assert_parse_value("\"\"", cJSON_String);
    reset();
    assert_parse_value("\"hello\"", cJSON_String);
    reset();
}

static void parse_value_should_parse_array(void)
{
    assert_parse_value("[]", cJSON_Array);
    reset();
}

static void parse_value_should_parse_object(void)
{
    assert_parse_value("{}", cJSON_Object);
    reset();
}

int main(void)
{
    /* initialize cJSON item */
    memset(item, 0, sizeof(cJSON));
    UNITY_BEGIN();
    RUN_TEST(parse_value_should_parse_null);
    RUN_TEST(parse_value_should_parse_true);
    RUN_TEST(parse_value_should_parse_false);
    RUN_TEST(parse_value_should_parse_number);
    RUN_TEST(parse_value_should_parse_string);
    RUN_TEST(parse_value_should_parse_array);
    RUN_TEST(parse_value_should_parse_object);
    return UNITY_END();
}
