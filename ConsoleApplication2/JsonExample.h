#pragma once
#include <sstream>
#include "JsonValue.h"
#include "JsonParse.h"
#include <string>
#include <iosfwd>
#include <iostream>

const wchar_t* EXAMPLE = L"  \
{ \
	\"string_name\" : \"string\tvalue and a \\\"quote\\\" and a unicode char \\u00BE and a c:\\\\path\\\\ or a \\/unix\\/path\\/ :D\", \
	\"bool_name\":true,\
	\"bool_second\" : FaLsE, \
	\"null_name\" : nULl, \
	\"negative\" : -34.276, \
	\"sub_object\" : { \
						\"foo\" : \"abc\", \
						 \"bar\" : 1.35e2, \
						 \"blah\" : { \"a\" : \"A\", \"b\" : \"B\", \"c\" : \"C\" } \
					}, \
	\"array_letters\" : [ \"a\", \"b\", \"c\", [ 1, 2, 3  ]  ] \
}    ";


// Example 1
void example1()
{
    // Parse example data
    JsonValue* value = JsonParse::Parse(EXAMPLE);

    // Did it go wrong?
    if (value == NULL)
    {
        printf("Example code failed to parse, did you change it?\r\n");
    }
    else
    {
        // Retrieve the main object
        JsonObject root = value->AsObject();
        if (value->IsObject() == false)
        {
            printf("The root element is not an object, did you change the example?\r\n");
        }
        else
        {
            //root = value->AsObject();

            // Retrieving a string
            if (root.find(L"string_name") != root.end() && root[L"string_name"]->IsString())
            {
                printf("string_name:\r\n");
                printf("------------\r\n");
                wprintf(root[L"string_name"]->AsString().c_str());
                printf("\r\n\r\n");
            }

            // Retrieving a boolean
            if (root.find(L"bool_second") != root.end() && root[L"bool_second"]->IsBool())
            {
                printf("bool_second:\r\n");
                printf("------------\r\n");
                printf(root[L"bool_second"]->AsBool() ? "it's true!" : "it's false!");
                printf("\r\n\r\n");
            }

            // Retrieving an array
            if (root.find(L"array_letters") != root.end() && root[L"array_letters"]->IsArray())
            {
                JsonArray array = root[L"array_letters"]->AsArray();
                printf("array_letters:\r\n");
                printf("--------------\r\n");
                for (unsigned int i = 0; i < array.size(); i++)
                {
                    wprintf(array[i]->Stringify().c_str());
                }
                printf("\r\n");
            }

            // Retrieving nested object
            if (root.find(L"sub_object") != root.end() && root[L"sub_object"]->IsObject())
            {
                printf("sub_object:\r\n");
                printf("-----------\r\n");
                wprintf(root[L"sub_object"]->Stringify().c_str());
                printf("\r\n\r\n");
            }
        }

        delete value;
    }
}

// Example 2
void example2()
{
    JsonObject root;

    // Adding a string
    root[L"test_string"] = new JsonValue(L"hello world");

    // Create a random integer array
    JsonArray array;
    srand((unsigned)time(0));
    for (int i = 0; i < 10; i++)
        array.push_back(new JsonValue((double)(rand() % 100)));
    root[L"sample_array"] = new JsonValue(array);

    // Create a value
    JsonValue* value = new JsonValue(root);

    // Print it
    wprintf(value->Stringify().c_str());

    std::cout << std::endl;

    // Clean up
    delete value;
}

// Example 3 : compact vs. prettyprint
void example3()
{
    const wchar_t* EXAMPLE3 =
        L"{\
	 \"SelectedTab\":\"Math\",\
	 	\"Widgets\":[\
			{\"WidgetPosition\":[0,369,800,582],\"WidgetIndex\":1,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,453,283,489],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F2.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":2,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,494,283,530],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F3.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":3,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[235,536,283,572],\"IsWidgetVisible\":-1,\"Caption\":\"On\",\"EnableCaption\":-1,\"Name\":\"F4.View\",\"CaptionPosition\":2,\"ControlWidth\":25,\"ControlHeight\":36,\"Font\":0,\"Value\":\"Off\",\"WidgetIndex\":4,\"WidgetType\":\"WidgetCheckbox.1\"},\
			{\"WidgetPosition\":[287,417,400,439],\"IsWidgetVisible\":-1,\"Caption\":\"\",\"EnableCaption\":0,\"Name\":\"F1.Equation\",\"CaptionPosition\":1,\"ControlWidth\":113,\"ControlHeight\":22,\"Font\":0,\"AlignText\":0,\"EnableBorder\":0,\"CaptionOnly\":0,\"Value\":\"FFT(C1)\",\"WidgetIndex\":9,\"WidgetType\":\"WidgetStaticText.1\"},\
			{\"WidgetPosition\":[191,409,230,445],\"IsWidgetVisible\":0,\"Caption\":\"F1\",\"EnableCaption\":0,\"Name\":\"F1.MeasureOpGui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Measurement To Graph\",\"Value\":\"Amplitude\",\"WidgetIndex\":17,\"WidgetType\":\"WidgetProcessorCombobox.1\"},\
			{\"WidgetPosition\":[191,409,230,445],\"IsWidgetVisible\":-1,\"Caption\":\"F1\",\"EnableCaption\":0,\"Name\":\"F1.Operator1gui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Math Operator\",\"Value\":\"FFT\",\"WidgetIndex\":25,\"WidgetType\":\"WidgetProcessorCombobox.1\"},\
			{\"WidgetPosition\":[191,452,230,487],\"IsWidgetVisible\":-1,\"Caption\":\"F2\",\"EnableCaption\":0,\"Name\":\"F2.Operator1gui\",\"CaptionPosition\":1,\"ControlWidth\":39,\"ControlHeight\":36,\"Font\":0,\"ButtonOnly\":-1,\"PickerTitle\":\"Select Math Operator\",\"Value\":\"Zoom\",\"WidgetIndex\":26,\"WidgetType\":\"WidgetProcessorCombobox.1\"}\
		]\
	 }";

    // Parse example data
    JsonValue* value = JsonParse::Parse(EXAMPLE3);
    if (value)
    {
        wprintf(L"-----------\r\n");
        wprintf(value->Stringify().c_str());
        wprintf(L"\r\n");
        wprintf(L"-----------\r\n");
        wprintf(value->Stringify().c_str());
        wprintf(L"\r\n");
        wprintf(L"-----------\r\n");
    }

    // Clean up
    delete value;
}

void example4()
{
    // Parse the example.
    JsonValue* main_object = JsonParse::Parse(EXAMPLE);
    if (main_object == NULL)
    {
        wprintf(L"Example code failed to parse, did you change it?\r\n");
    }
    else if (!main_object->IsObject())
    {
        wprintf(L"Example code is not an object, did you change it?\r\n");
        delete main_object;
    }
    else
    {
        // Print the main object.
        wprintf(L"Main object:\r\n");
        wprintf(main_object->Stringify().c_str());
        wprintf(L"-----------\r\n");

        // Fetch the keys and print them out.
        std::vector<std::wstring> keys = main_object->ObjectKeys();

        std::vector<std::wstring>::iterator iter = keys.begin();
        while (iter != keys.end())
        {
            wprintf(L"Key: ");
            wprintf((*iter).c_str());
            wprintf(L"\r\n");

            // Get the key's value.
            JsonValue* key_value = main_object->Child((*iter).c_str());
            if (key_value)
            {
                wprintf(L"Value: ");
                wprintf(key_value->Stringify().c_str());
                wprintf(L"\r\n");
                wprintf(L"-----------\r\n");
            }

            // Next key.
            iter++;
        }

        delete main_object;
    }
}