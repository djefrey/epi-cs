/*
** EPITECH PROJECT, 2022
** epi-cs
** File description:
** JSONParser
*/

#pragma once

#include <string>
#include <memory>

#define JSON_CHECK_TYPE(token, type) (if (token.type != type) { throw InvalidJSONDataType(); })
#define JSON_CHECK_KEY(token) (if (token.type != JSMN_STRING || token.size == 0) { throw InvalidJSONFormat(); })

#include "external/cgltf.h"

namespace json {
    class InvalidJSONDataType {};
    class InvalidJSONFormat {};
    class UnknownJSONField {};

    class JSONObject {
        jsmn_parser &_parser;
        std::unique_ptr<jsmntok_t> &_tokens;
        const std::string &_json;

        unsigned int _start;
        unsigned int _end;
        unsigned int _childs;

        jsmntok_t *getTokenFromName(const std::string &field)
        {
            jsmntok_t *tokens = _tokens.get();
            jsmntok_t token;

            for (unsigned int i = _start; i < _end; i++) {
                token = *(tokens + i);
                JSON_CHECK_KEY(token);
                if (field.size() == token.size
                && !strncmp(field.c_str(), _json.c_str() + token.start, token.size)) {
                    return tokens + i;
                }
            }
            return nullptr;
        }

        public:
        JSONObject(jsmn_parser &parser, std::unique_ptr<jsmntok_t> &tokens, const std::string &json, jsmntok_t &token)
            : _parser(parser), _tokens(tokens), _json(json), _start(token.start), _end(token.end), _childs(token.size)
        {
        }

        JSONObject getObject(const std::string &field)
        {
            jsmntok_t *token = getTokenFromName(field);

            if (token == NULL)
                throw UnknownJSONField();
            JSON_CHECK_TYPE(*token, JSMN_OBJECT);
            return JSONObject(_parser, _tokens, _json, *token);
        }

        std::string getString(const std::string &field)
        {
            jsmntok_t *token = getTokenFromName(field);
            std::string str;

            if (token == NULL)
                throw UnknownJSONField();
            JSON_CHECK_TYPE(*token, JSMN_STRING);
            str.reserve(token->size);
            strncpy(str.c_str(), _json.c_str() + token->start, token->size);
            return str;
        }

        bool getBool(const std::string &field)
        {
            jsmntok_t *token = getTokenFromName(field);

            if (token == NULL)
                throw UnknownJSONField();
            JSON_CHECK_TYPE(*token, JSMN_PRIMITIVE);
            return !strncmp(_json.c_str() + token->start, "true", 4);
        }

        int getInt(const std::string &field)
        {
            jsmntok_t *token = getTokenFromName(field);
            char buf[64] = {0};

            if (token == NULL)
                throw UnknownJSONField();
            JSON_CHECK_TYPE(*token, JSMN_PRIMITIVE);
            if (token->size > 64)
                throw InvalidJSONFormat();
            strncpy(buf, _json.c_str() + token->start, 64);
            return atoi(buf);
        }

        int getFloat(const std::string &field)
        {
            jsmntok_t *token = getTokenFromName(field);
            char buf[64] = {0};

            if (token == NULL)
                throw UnknownJSONField();
            JSON_CHECK_TYPE(*token, JSMN_PRIMITIVE);
            if (token->size > 64)
                throw InvalidJSONFormat();
            strncpy(buf, _json.c_str() + token->start, 64);
            return atof(buf);
        }
    };

    class JSONParser {
        jsmn_parser _parser = { 0 };
        unsigned int _nbTokens = 0;
        std::unique_ptr<jsmntok_t> _tokens = nullptr;
        const std::string _json;

        public:
        JSONParser(const std::string &json) : _json(json)
        {
            _nbTokens = jsmn_parse(&_parser, _json.c_str(), _json.size(), nullptr, 0);
            if (_nbTokens == 0)
                return;
            _tokens = std::unique_ptr<jsmntok_t>(new jsmntok_t[_nbTokens]);
            jsmn_init(&_parser);
            jsmn_parse(&_parser, _json.c_str(), _json.size(), _tokens.get(), _nbTokens);
            _tokens.get()[_nbTokens].type = JSMN_UNDEFINED;
        }

        JSONObject getRoot()
        {
            return JSONObject(_parser, _tokens, _json, *_tokens);
        }
    };
}
