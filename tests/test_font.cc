#include <SDL2/SDL_main.h>

#include <SDL2pp/SDLTTF.hh>
#include <SDL2pp/Font.hh>
#include <SDL2pp/Exception.hh>

#include "testing.h"
#include "movetest.hh"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	SDLTTF ttf;
	Font font(TESTDATA_DIR "/Vera.ttf", 30);

	MOVE_TEST(Font, font, Get, nullptr);

	{
		// Font style
		EXPECT_EQUAL(font.GetStyle(), TTF_STYLE_NORMAL);

		font.SetStyle(TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH);
		EXPECT_EQUAL(font.GetStyle(), TTF_STYLE_BOLD | TTF_STYLE_ITALIC | TTF_STYLE_UNDERLINE | TTF_STYLE_STRIKETHROUGH);

		font.SetStyle();
		EXPECT_EQUAL(font.GetStyle(), TTF_STYLE_NORMAL);
	}

	{
		// Outline
		EXPECT_EQUAL(font.GetOutline(), 0);

		font.SetOutline(2);
		EXPECT_EQUAL(font.GetOutline(), 2);

		font.SetOutline();
		EXPECT_EQUAL(font.GetOutline(), 0);
	}

	{
		// Hinting
		EXPECT_EQUAL(font.GetHinting(), TTF_HINTING_NORMAL);

		font.SetHinting(TTF_HINTING_LIGHT);
		EXPECT_EQUAL(font.GetHinting(), TTF_HINTING_LIGHT);

		font.SetHinting();
		EXPECT_EQUAL(font.GetHinting(), TTF_HINTING_NORMAL);
	}

	{
		// Kerning
		EXPECT_EQUAL(font.GetKerning(), true);

		font.SetKerning(false);
		EXPECT_EQUAL(font.GetKerning(), false);

		font.SetKerning();
		EXPECT_EQUAL(font.GetKerning(), true);
	}

	{
		// Metrics
		EXPECT_EQUAL(font.GetHeight(), 36);
		EXPECT_EQUAL(font.GetAscent(), 28);
		EXPECT_EQUAL(font.GetDescent(), -7);
		EXPECT_EQUAL(font.GetLineSkip(), 35);
	}

	{
		// Faces
		EXPECT_EQUAL(font.GetNumFaces(), 1);
	}

	{
		// Fixed width
		EXPECT_EQUAL(font.IsFixedWidth(), false);
	}

	{
		// Names
		auto family = font.GetFamilyName();
		auto style = font.GetStyleName();

		EXPECT_TRUE(family && *family == "Bitstream Vera Sans");
		EXPECT_TRUE(style && *style == "Roman");
	}

	{
		// Glyphs provided
		EXPECT_TRUE(font.IsGlyphProvided(u'A'));
		EXPECT_TRUE(font.IsGlyphProvided(u'¼'));
		EXPECT_TRUE(!font.IsGlyphProvided(u'л'));
		EXPECT_TRUE(!font.IsGlyphProvided(u'Ы'));
	}

	{
		// Glyph metrics
		int minx, maxx, miny, maxy, advance;

		// Why doesn't TTF_GlyphMetrics on non-existing glyph not return -1?!
		//EXPECT_EXCEPTION(font.GetGlyphMetrics(u'л', minx, maxx, miny, maxy, advance), Exception);

		EXPECT_NO_EXCEPTION(font.GetGlyphMetrics(u'A', minx, maxx, miny, maxy, advance));

		EXPECT_EQUAL(minx, 0);
		EXPECT_EQUAL(maxx, 20);
		EXPECT_EQUAL(miny, 0);
		EXPECT_EQUAL(maxy, 22);
		EXPECT_EQUAL(advance, 21);

		EXPECT_EQUAL(font.GetGlyphRect(u'A'), Rect(0, 0, 20, 22));
		EXPECT_EQUAL(font.GetGlyphAdvance(u'A'), 21);

		// Text size
		EXPECT_EQUAL(font.GetSizeText("AA"), Point(43, 36));
		EXPECT_EQUAL(font.GetSizeUTF8(u8"AA"), Point(43, 36));
		EXPECT_EQUAL(font.GetSizeUNICODE(u"AA"), Point(43, 36));
	}

	{
		// Rendering
		// XXX: add real pixel color tests
		EXPECT_EQUAL(font.RenderText_Solid("AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUTF8_Solid(u8"AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUNICODE_Solid(u"AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));

		EXPECT_EQUAL(font.RenderText_Shaded("AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUTF8_Shaded(u8"AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUNICODE_Shaded(u"AA", SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 0, 255}).GetSize(), Point(43, 36));

		EXPECT_EQUAL(font.RenderText_Blended("AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUTF8_Blended(u8"AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));
		EXPECT_EQUAL(font.RenderUNICODE_Blended(u"AA", SDL_Color{255, 255, 255, 255}).GetSize(), Point(43, 36));
	}
END_TEST()
