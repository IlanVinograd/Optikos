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
// TODO: SDF Fonts

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
    RenderData generateTextQuads(const std::string& text, const Vec2& position,
                                 const uint32_t& width, const uint32_t& height, const Clip& clip,
                                 const std::string& fontName  = DEFAULT0_FONT,
                                 const Color&       textColor = DEFAULT_COLOR);

    unsigned int                      getAtlasTextureId(std::string fontName = DEFAULT0_FONT) const;
    const std::vector<unsigned char>& getAtlasData(std::string fontName = DEFAULT0_FONT) const;
    unsigned int                      getAtlasSize(std::string fontName = DEFAULT0_FONT) const;
    Vec2 getSizeText(const std::string& text, std::string fontName = DEFAULT0_FONT);
    int getPosText(double startText, const std::string& text, std::string fontName = DEFAULT0_FONT);

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
        unsigned int                                 atlasSize      = 0;
        float                                        fontSize       = DEFAULT0_FONTSIZE;
        FT_Face                                      face;
        float                                        textHeight = 0;
        float                                        textLength = 0;
    };

    std::unordered_map<std::string, Atlas> m_Atlases;
};

}  // namespace Optikos

#endif /* TEXTFONT_H */