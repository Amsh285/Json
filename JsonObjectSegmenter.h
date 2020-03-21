#ifndef JSONOBJECTSEGMENTER_H
#define JSONOBJECTSEGMENTER_H

#include<string>
#include<tuple>
#include<vector>
#include<assert.h>
#include<stdexcept>
#include<ostream>
#include<iostream>
#include<sstream>

#include "Utilities.h"
#include "StringHelper.h"
#include "JsonObjectSegmenterIgnoreSignState.h"
#include "JsonObjectSegmenterKeyValuePairValidationState.h"

using namespace GlobalJsonDefinitions;

class JsonObjectSegmenter
{
    public:
        JsonObjectSegmenter();
        virtual ~JsonObjectSegmenter();

        void SegmentJsonString(std::vector<std::string>& target, std::string source, JsonElementType type);

        void PrintSegments(std::ostream* targetStream, std::vector<std::string>& source);
    protected:

    private:
};

#endif // JSONOBJECTSEGMENTER_H
