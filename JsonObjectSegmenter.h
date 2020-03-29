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

#include "JsonUtilities.h"
#include "StringHelper.h"
#include "JsonObjectSegmenterIgnoreSignState.h"
#include "InsideStringLiteralState.h"

class JsonObjectSegmenter
{
    public:
        JsonObjectSegmenter();
        virtual ~JsonObjectSegmenter();

        void SegmentJsonString(std::vector<std::string>& target, std::string source, GlobalJsonDefinitions::JsonElementType type);

        void PrintSegments(std::ostream* targetStream, std::vector<std::string>& source);
    protected:

    private:
};

#endif // JSONOBJECTSEGMENTER_H
