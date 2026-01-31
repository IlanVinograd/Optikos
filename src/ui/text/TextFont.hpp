#ifndef TEXTFONT_H
#define TEXTFONT_H

// TODO: defines for size of atlas

#include <ft2build.h>

#include "ui/IWidget.hpp"
#include "utilities/logger.hpp"
#include "utilities/vec.hpp"

#include FT_FREETYPE_H

class TextFont
{
   public:
    static TextFont& getInstance()
    {
        static TextFont instance;
        return instance;
    }

    TextFont(const TextFont&) = delete;
    TextFont& operator=(const TextFont&) = delete;

    ~TextFont();

    void       loadFont(std::string_view fontPath, int fontSize = 16);
    void       setAtlasTextureId(unsigned int id);
    RenderData generateTextQuads(const std::string& text, vec2 position);

    unsigned int                      getAtlasTextureId() const;
    const std::vector<unsigned char>& getAtlasData() const;

    int getAtlasWidth() const;
    int getAtlasHeight() const;

   private:
    TextFont();

    void generateAtlas(int fontSize);

    FT_Library m_library;
    FT_Face    m_face;

    std::vector<unsigned char> m_atlasData;
    unsigned int               m_atlasTextureId = 0;
    int                        m_fontSize       = 16;

    int m_atlasWidth  = 1024;
    int m_atlasHeight = 1024;

    struct Character
    {
        int atlasX, atlasY;
        int width, height;
        int bearing_x, bearing_y;
        int advance;
    };
    //TODO: create struct with named Atlas that have chars and the atlas;
    std::unordered_map<unsigned char, Character> m_characters;
    Color                               m_textColor{255, 255, 255, 255};
    bool                                m_initialized = false;
};

#endif /* TEXTFONT_H */