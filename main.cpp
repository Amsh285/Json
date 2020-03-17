#include <iostream>

#include "Utilities.h"
#include "JsonObject.h"
#include "JsonValue.h"

using namespace std;

int main()
{
    JsonObject *person = Create::A.JsonObject()
        //.WithName("Person")
        .WithJsonObjectType(JsonObjectType_Object)
        .Build();

    JsonValue* firstName = Create::A.JsonValue()
        .WithName("Vorname")
        .WithValue("Sepp")
        .WithParent(person)
        .Build();

    JsonValue* lastName = Create::A.JsonValue()
        .WithName("Alter")
        .WithValue(33)
        .WithParent(person)
        .Build();

    JsonObject *address = Create::A.JsonObject()
        .WithName("Addresse")
        .WithValues( [](Create::JsonValueListBuider builder){
            return builder
                .WithValue("Strasse", "Seppgasse 24")
                .WithValue("TuerNr", 12)
                .WithValue("Postleitzahl", 1337)
                .WithValue("Ort", "Badgerhausen")
                .Build();
        })
        .WithJsonObjectType(JsonObjectType_Object)
        .WithParent(person)
        .Build();

    cout << person->ToJsonString() << endl;

    delete person;

    return 0;
}
