#include <iostream>

#include "Utilities.h"
#include "JsonObject.h"
#include "JsonValue.h"

using namespace std;

int main()
{
    // Ebene speichern für die Formatierung

    JsonObject *person = Create::A.JsonObject()
        .WithName("Person")
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
        .WithJsonObjectType(JsonObjectType_Object)
        .WithParent(person)
        .Build();

    JsonValue* street = Create::A.JsonValue()
        .WithName("Strasse")
        .WithValue("Seppgasse 24")
        .WithParent(address)
        .Build();

    JsonValue* doorNumber = Create::A.JsonValue()
        .WithName("TuerNr:")
        .WithValue(12)
        .WithParent(address)
        .Build();

    cout << person->ToJsonString() << endl;

    delete person;

    return 0;
}
