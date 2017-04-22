bool Font::create(const string &name, unsigned size, Font::Style style)
{
    font->font = pango_font_description_new();

    pango_font_description_set_family(font->font, name);
    pango_font_description_set_size(font->font, size * PANGO_SCALE);

    if ((style & Style::Italic) == Style::Italic) {
        pango_font_description_set_style(font->font, PANGO_STYLE_OBLIQUE);
    } else {
        pango_font_description_set_style(font->font, PANGO_STYLE_NORMAL);
    }

    if ((style & Style::Bold) == Style::Bold) {
        pango_font_description_set_weight(font->font, PANGO_WEIGHT_BOLD);
    } else {
        pango_font_description_set_weight(font->font, PANGO_WEIGHT_NORMAL);
    }

    return true;
}

Font::Font(void)
{
    font = new Font::Data;
    font->font = 0;
}

Font::~Font(void)
{
    if (font->font) {
        pango_font_description_free(font->font);
    }

    delete font;
}
