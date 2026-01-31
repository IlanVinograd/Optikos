#include "ui/text/TextFont.hpp"

TextFont::TextFont()
{
    int error = FT_Init_FreeType(&m_library);
    if (error)
    {
        LOG_DEBUG("inside [FT_Init_FreeType] error occured", "log");
        return;
    }
}

TextFont::~TextFont()
{
    if (m_face)
    {
        FT_Done_Face(m_face);
    }
    FT_Done_FreeType(m_library);
}

void TextFont::loadFont(std::string_view fontPath, int fontSize)
{
    if (fontPath.empty())
    {
        LOG_DEBUG("Font path is empty", "log");
        return;
    }

    if (m_face)
    {
        FT_Done_Face(m_face);
        m_face = nullptr;
    }

    int error = FT_New_Face(m_library, std::data(fontPath), 0, &m_face);
    if (error == FT_Err_Unknown_File_Format)
    {
        LOG_DEBUG("inside [FT_New_Face] unknown file format", "log");
        return;
    }
    if (error)
    {
        LOG_DEBUG("inside [FT_New_Face] error occured", "log");
        return;
    }

    m_fontSize = fontSize;
    generateAtlas(fontSize);
    m_initialized = true;
}

void TextFont::generateAtlas(int fontSize)
{
    if (!m_face)
    {
        LOG_DEBUG("Face not initialized in generateAtlas", "log");
        return;
    }

    FT_Set_Pixel_Sizes(m_face, 0, fontSize);

    m_atlasData.assign(m_atlasWidth * m_atlasHeight, 0);
    m_characters.clear();

    int xpos         = 0;
    int ypos         = 0;
    int maxRowHeight = 0;

    for (unsigned char c = 32; c < 128; c++)
    {
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            continue;
        }

        auto& bitmap = m_face->glyph->bitmap;

        if (xpos + (int) bitmap.width >= m_atlasWidth)
        {
            xpos = 0;
            ypos += maxRowHeight + 1;
            maxRowHeight = 0;
        }

        if (ypos + (int) bitmap.rows >= m_atlasHeight)
        {
            LOG_ERROR("Font atlas is full! Increase atlas size or decrease font size.", "log");
            break;
        }

        for (int row = 0; row < (int) bitmap.rows; ++row)
        {
            for (int col = 0; col < (int) bitmap.width; ++col)
            {
                int atlasIdx          = (ypos + row) * m_atlasWidth + (xpos + col);
                int glyphIdx          = row * bitmap.pitch + col;
                m_atlasData[atlasIdx] = bitmap.buffer[glyphIdx];
            }
        }

        Character character{xpos,
                            ypos,
                            (int) bitmap.width,
                            (int) bitmap.rows,
                            m_face->glyph->bitmap_left,
                            m_face->glyph->bitmap_top,
                            (int) (m_face->glyph->advance.x >> 6)};

        m_characters[c] = character;

        if ((int) bitmap.rows > maxRowHeight) maxRowHeight = (int) bitmap.rows;
        xpos += bitmap.width + 1;
    }
}

RenderData TextFont::generateTextQuads(const std::string& text, vec2 position)
{
    RenderData data;

    if (!m_initialized)
    {
        LOG_DEBUG("TextFont not initialized, call loadFont() first", "log");
        return data;
    }

    float        xpos   = position.x;
    //float        ypos   = position.y;
    unsigned int offset = 0;
    for (const auto& symbol : text)
    {
        if (m_characters.find(symbol) == m_characters.end())
        {
            LOG_DEBUG("There is no symbol: " + std::to_string(symbol) + "inside atlas", "log");
            continue;
        }

        Character ch = m_characters[(unsigned char) symbol];

        float x = xpos + ch.bearing_x;
        float y = (position.y + (30 / 2) + (m_fontSize / 3)) - ch.bearing_y;
        float w = static_cast<float>(ch.width);
        float h = static_cast<float>(ch.height);

        float u1 = static_cast<float>(ch.atlasX) / m_atlasWidth;
        float v1 = static_cast<float>(ch.atlasY) / m_atlasHeight;
        float u2 = u1 + static_cast<float>(ch.width) / m_atlasWidth;
        float v2 = v1 + static_cast<float>(ch.height) / m_atlasHeight;

        data.vertices.insert(data.vertices.end(), {x, y, m_textColor.r, m_textColor.g,
                                                   m_textColor.b, m_textColor.a, u1, v1});
        data.vertices.insert(data.vertices.end(), {x + w, y, m_textColor.r, m_textColor.g,
                                                   m_textColor.b, m_textColor.a, u2, v1});
        data.vertices.insert(data.vertices.end(), {x, y + h, m_textColor.r, m_textColor.g,
                                                   m_textColor.b, m_textColor.a, u1, v2});
        data.vertices.insert(data.vertices.end(), {x + w, y + h, m_textColor.r, m_textColor.g,
                                                   m_textColor.b, m_textColor.a, u2, v2});

        data.indices.insert(data.indices.end(), {offset + 0, offset + 1, offset + 2, offset + 1,
                                                 offset + 3, offset + 2});
        offset += 4;

        xpos += ch.advance;
    }

    return data;
}

int TextFont::getAtlasWidth() const
{
    return m_atlasWidth;
}

int TextFont::getAtlasHeight() const
{
    return m_atlasHeight;
}

unsigned int TextFont::getAtlasTextureId() const
{
    return m_atlasTextureId;
}

void TextFont::setAtlasTextureId(unsigned int id)
{
    m_atlasTextureId = id;
}

const std::vector<unsigned char>& TextFont::getAtlasData() const
{
    return m_atlasData;
}