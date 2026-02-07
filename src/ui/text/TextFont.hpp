#ifndef TEXTFONT_H
#define TEXTFONT_H

#include <ft2build.h>

#include "ui/IWidget.hpp"
#include "utilities/logger.hpp"
#include "utilities/vec.hpp"

#include FT_FREETYPE_H

namespace Optikos
{
inline constexpr const char* DEFAULT0_FONT = "default0";
float constexpr DEFAULT0_FONTSIZE          = 16.0;

unsigned int constexpr DEFAULT_CHAR_START = 32;
unsigned int constexpr DEFAULT_CHAR_END   = 126;
Color constexpr DEFAULT_COLOR             = Color{255, 255, 255, 255};

// TODO: check if better to use one huge atlas or some small atlases.
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

    void       loadFont(std::string_view fontPath, std::string fontName = DEFAULT0_FONT,
                        float fontSize = DEFAULT0_FONTSIZE);
    RenderData generateTextQuads(const std::string& text, Vec2 position, uint32_t width,
                                 uint32_t height, std::string fontName = DEFAULT0_FONT);

    unsigned int                      getAtlasTextureId(std::string fontName = DEFAULT0_FONT) const;
    const std::vector<unsigned char>& getAtlasData(std::string fontName = DEFAULT0_FONT) const;
    unsigned int                      getAtlasSize(std::string fontName = DEFAULT0_FONT) const;

    void setAtlasTextureId(unsigned int id, std::string fontName = DEFAULT0_FONT);

   private:
    TextFont();

    void         generateAtlas(std::string fontName, float fontSize);
    unsigned int CalculateAtlasSize(float fontSize);

    FT_Library m_library;
    FT_Face    m_face;

    struct Character
    {
        int atlasX, atlasY;
        int width, height;
        int bearing_x, bearing_y;
        int advance;
    };

    struct Atlas
    {
        std::unordered_map<unsigned char, Character> characters;
        std::vector<unsigned char>                   atlasData;
        unsigned int                                 atlasTextureId = 0;
        Color                                        textColor      = DEFAULT_COLOR;
        unsigned int                                 atlasSize      = 0;
        float                                        fontSize       = DEFAULT0_FONTSIZE;
        FT_Face                                      face;
    };

    std::unordered_map<std::string, Atlas> m_Atlases;
};

}  // namespace Optikos

#endif /* TEXTFONT_H */