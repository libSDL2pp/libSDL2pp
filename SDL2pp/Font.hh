/*
  libSDL2pp - C++ bindings/wrapper for SDL2
  Copyright (C) 2014-2015 Dmitry Marakasov <amdmi3@amdmi3.ru>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef SDL2PP_FONT_HH
#define SDL2PP_FONT_HH

#include <string>

#include <SDL_ttf.h>

#include <SDL2pp/Optional.hh>
#include <SDL2pp/Point.hh>
#include <SDL2pp/Surface.hh>
#include <SDL2pp/Export.hh>

namespace SDL2pp {

class RWops;

////////////////////////////////////////////////////////////
/// \brief Holder of a loaded font
///
/// \ingroup ttf
///
/// \headerfile SDL2pp/Font.hh
///
/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC56
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT Font {
private:
	TTF_Font* font_; ///< Managed TTF_Font object

public:

	///@{
	/// \name Construction and destruction

	////////////////////////////////////////////////////////////
	/// \brief Construct from existing TTF_Font structure
	///
	/// \param[in] font Existing TTF_Font to manage
	///
	////////////////////////////////////////////////////////////
	explicit Font(TTF_Font* font);

	////////////////////////////////////////////////////////////
	/// \brief Loads font from .ttf or .fon file
	///
	/// \param[in] file Pointer File name to load font from
	/// \param[in] ptsize %Point size (based on 72DPI) to load font as. This basically translates to pixel height
	/// \param[in] index Choose a font face from a file containing multiple font faces. The first face is always index 0
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC14
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC16
	///
	////////////////////////////////////////////////////////////
	Font(const std::string& file, int ptsize, long index = 0);

	////////////////////////////////////////////////////////////
	/// \brief Loads font with RWops
	///
	/// \param[in] rwops RWops to load font from
	/// \param[in] ptsize %Point size (based on 72DPI) to load font as. This basically translates to pixel height
	/// \param[in] index Choose a font face from a file containing multiple font faces. The first face is always index 0
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC15
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC17
	///
	////////////////////////////////////////////////////////////
	Font(RWops& rwops, int ptsize, long index = 0);

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC18
	///
	////////////////////////////////////////////////////////////
	virtual ~Font();

	///@}

	///@{
	/// \name Copy and move

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::Font object to move data from
	///
	////////////////////////////////////////////////////////////
	Font(Font&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment
	///
	/// \param[in] other SDL2pp::Font object to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	Font& operator=(Font&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Font(const Font&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	Font& operator=(const Font&) = delete;

	///@}

	///@{
	/// \name Compatibility with legacy SDL code

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed TTF_Font structure
	///
	/// \returns Pointer to managed TTF_Font structure
	///
	////////////////////////////////////////////////////////////
	TTF_Font* Get() const;

	///@{
	/// \name Attributes: font style

	////////////////////////////////////////////////////////////
	/// \brief Get the rendering style of the loaded font
	///
	/// \returns The style as a bitmask composed of the following masks:
	///          TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE,
	///          TTF_STYLE_STRIKETHROUGH. If no style is set then
	///          TTF_STYLE_NORMAL is returned
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC21
	///
	////////////////////////////////////////////////////////////
	int GetStyle() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the rendering style of the loaded font
	///
	/// \param[in] style The style as a bitmask composed of the following masks:
	///                  TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE,
	///                  TTF_STYLE_STRIKETHROUGH. If no style is desired then use
	///                  TTF_STYLE_NORMAL, which is the default.
	///
	/// \note This will flush the internal cache of previously rendered
	/// glyphs, even if there is no change in style, so it may be best
	/// to check the current style by using GetStyle() first
	///
	/// \note TTF_STYLE_UNDERLINE may cause surfaces created by TTF_RenderGlyph_*
	/// functions to be extended vertically, downward only, to encompass the
	/// underline if the original glyph metrics didn't allow for the underline
	/// to be drawn below. This does not change the math used to place a glyph
	/// using glyph metrics.
	/// On the other hand TTF_STYLE_STRIKETHROUGH doesn't extend the glyph,
	/// since this would invalidate the metrics used to position the glyph
	/// when blitting, because they would likely be extended vertically upward.
	/// There is perhaps a workaround, but it would require programs to be
	/// smarter about glyph blitting math than they are currently designed for.
	/// Still, sometimes the underline or strikethrough may be outside of the
	/// generated surface, and thus not visible when blitted to the screen.
	/// In this case, you should probably turn off these styles and draw your
	/// own strikethroughs and underlines.
	///
	/// \returns Reference to self
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC22
	///
	////////////////////////////////////////////////////////////
	Font& SetStyle(int style = TTF_STYLE_NORMAL);

	////////////////////////////////////////////////////////////
	/// \brief Get the current outline size of the loaded font
	///
	/// \returns The size of the outline currently set on the font, in pixels
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC23
	///
	////////////////////////////////////////////////////////////
	int GetOutline() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the outline pixel width of the loaded font
	///
	/// \param[in] outline The size of outline desired, in pixels.
	///                    Use 0 (zero) to turn off outlining.
	///
	/// \note This will flush the internal cache of previously rendered
	/// glyphs, even if there is no change in outline size, so it may be best
	/// to check the current outline size by using GetOutline() first
	///
	/// \returns Reference to self
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC24
	///
	////////////////////////////////////////////////////////////
	Font& SetOutline(int outline = 0);

	///@}

	///@{
	/// \name Attributes: font settings

	////////////////////////////////////////////////////////////
	/// \brief Get the current hinting setting of the loaded font
	///
	/// \returns The hinting type matching one of the following defined values:
	///          TTF_HINTING_NORMAL, TTF_HINTING_LIGHT, TTF_HINTING_MONO,
	///          TTF_HINTING_NONE. If no hinting is set then TTF_HINTING_NORMAL is returned
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC25
	///
	////////////////////////////////////////////////////////////
	int GetHinting() const;

	////////////////////////////////////////////////////////////
	/// \brief Set the hinting of the loaded font
	///
	/// \param[in] hinting The hinting setting desired, which is one of:
	///                    TTF_HINTING_NORMAL, TTF_HINTING_LIGHT, TTF_HINTING_MONO,
	///                    TTF_HINTING_NONE. The default is TTF_HINTING_NORMAL
	///
	/// You should experiment with this setting if you know which font
	/// you are using beforehand, especially when using smaller sized
	/// fonts. If the user is selecting a font, you may wish to let them
	/// select the hinting mode for that font as well
	///
	/// \note This will flush the internal cache of previously rendered
	/// glyphs, even if there is no change in hinting, so it may be best
	/// to check the current hinting by using GetHinting() first
	///
	/// \returns Reference to self
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC26
	///
	////////////////////////////////////////////////////////////
	Font& SetHinting(int hinting = TTF_HINTING_NORMAL);

	////////////////////////////////////////////////////////////
	/// \brief Get the current kerning setting of the loaded font
	///
	/// \returns False if kerning is disabled. True when enabled.
	///          The default for a newly loaded font is true, enabled
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC27
	///
	////////////////////////////////////////////////////////////
	bool GetKerning() const;

	////////////////////////////////////////////////////////////
	/// \brief Set whether to use kerning when rendering the loaded font
	///
	/// \param[in] allowed False to disable kerning, true to enable kerning.
	///                    The default is true, enabled
	///
	/// Set whether to use kerning when rendering the loaded font.
	/// This has no effect on individual glyphs, but rather when
	/// rendering whole strings of characters, at least a word at
	/// a time. Perhaps the only time to disable this is when kerning
	/// is not working for a specific font, resulting in overlapping
	/// glyphs or abnormal spacing within words.
	///
	/// \returns Reference to self
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC28
	///
	////////////////////////////////////////////////////////////
	Font& SetKerning(bool allowed = true);

	///@}

	///@{
	/// \name Attributes: font metrics

	////////////////////////////////////////////////////////////
	/// \brief Get the maximum pixel height of all glyphs of the loaded font
	///
	/// \returns The maximum pixel height of all glyphs in the font
	///
	/// You may use this height for rendering text as close together
	/// vertically as possible, though adding at least one pixel height
	/// to it will space it so they can't touch. Remember that SDL_ttf
	/// doesn't handle multiline printing, so you are responsible for
	/// line spacing, see the GetLineSkip() as well.
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC29
	///
	////////////////////////////////////////////////////////////
	int GetHeight() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the maximum pixel ascent of all glyphs of the loaded font
	///
	/// \returns The maximum pixel ascent of all glyphs in the font
	///
	/// This can also be interpreted as the distance from the top of
	/// the font to the baseline. It could be used when drawing an
	/// individual glyph relative to a top point, by combining it
	/// with the glyph's maxy metric to resolve the top of the
	/// rectangle used when blitting the glyph on the screen.
	///
	/// \code{.cpp}
	/// rect.y = top + Font.GetAscent() - glyph_metric.maxy;
	/// \endcode
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC30
	///
	////////////////////////////////////////////////////////////
	int GetAscent() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the maximum pixel descent of all glyphs of the loaded font
	///
	/// \returns The maximum pixel height of all glyphs in the font
	///
	/// This can also be interpreted as the distance from the
	/// baseline to the bottom of the font.
	/// It could be used when drawing an individual glyph relative
	/// to a bottom point, by combining it with the glyph's maxy
	/// metric to resolve the top of the rectangle used when blitting
	/// the glyph on the screen.
	///
	/// \code{.cpp}
	/// rect.y = bottom - TTF_FontDescent(font) - glyph_metric.maxy;
	/// \endcode
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC31
	///
	////////////////////////////////////////////////////////////
	int GetDescent() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the recommended pixel height of a rendered line of text of the loaded font
	///
	/// \returns The maximum pixel height of all glyphs in the font
	///
	/// This is usually larger than the GetHeight() of the font
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC32
	///
	////////////////////////////////////////////////////////////
	int GetLineSkip() const;

	///@}

	///@{
	/// \name Attributes: face attributes

	////////////////////////////////////////////////////////////
	/// \brief Get the number of faces ("sub-fonts") available in the loaded font
	///
	/// \returns The number of faces in the font
	///
	/// This is a count of the number of specific fonts (based on size
	/// and style and other typographical features perhaps) contained
	/// in the font itself. It seems to be a useless fact to know,
	/// since it can't be applied in any other SDL_ttf functions.
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC33
	///
	////////////////////////////////////////////////////////////
	long GetNumFaces() const;

	////////////////////////////////////////////////////////////
	/// \brief Test if the current font face of the loaded font is a fixed width font
	///
	/// \returns True if font is a fixed width font. False if not a fixed width font
	///
	/// Fixed width fonts are monospace, meaning every character
	/// that exists in the font is the same width, thus you can
	/// assume that a rendered string's width is going to be the
	/// result of a simple calculation:
	///
	/// \code{.cpp}
	/// glyph_width * string_length
	/// \endcode
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC34
	///
	////////////////////////////////////////////////////////////
	bool IsFixedWidth() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the current font face family name from the loaded font
	///
	/// \returns The current family name of of the face of the font, or NullOpt perhaps
	///
	/// This function may return NullOpt, in which case the information is not available.
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC35
	///
	////////////////////////////////////////////////////////////
	Optional<std::string> GetFamilyName() const;

	////////////////////////////////////////////////////////////
	/// \brief Get the current font face style name from the loaded font
	///
	/// \returns The current style name of of the face of the font, or NullOpt perhaps
	///
	/// This function may return NullOpt, in which case the information is not available
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC36
	///
	////////////////////////////////////////////////////////////
	Optional<std::string> GetStyleName() const;

	///@}

	///@{
	/// \name Attributes: glyphs

	////////////////////////////////////////////////////////////
	/// \brief Get the status of the availability of the glyph from the loaded font
	///
	/// \param[in] ch Unicode character to test glyph availability of
	///
	/// \returns The index of the glyph for ch in font, or 0 for an undefined character code
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC37
	///
	////////////////////////////////////////////////////////////
	int IsGlyphProvided(Uint16 ch) const;

	////////////////////////////////////////////////////////////
	/// \brief Get glyph metrics of the UNICODE char
	///
	/// \param[in] ch UNICODE char to get the glyph metrics for
	/// \param[out] minx Variable to store the returned minimum X offset into
	/// \param[out] maxx Variable to store the returned maximum X offset into
	/// \param[out] miny Variable to store the returned minimum Y offset into
	/// \param[out] maxy Variable to store the returned maximum Y offset into
	/// \param[out] advance Variable to store the returned advance offset into
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC38
	/// \see http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
	///
	////////////////////////////////////////////////////////////
	void GetGlyphMetrics(Uint16 ch, int& minx, int& maxx, int& miny, int& maxy, int& advance) const;

	////////////////////////////////////////////////////////////
	/// \brief Get rect part of glyph metrics of the UNICODE char
	///
	/// \param[in] ch UNICODE char to get the glyph metrics for
	///
	/// \returns Rect representing glyph offset info
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC38
	/// \see http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
	///
	////////////////////////////////////////////////////////////
	Rect GetGlyphRect(Uint16 ch) const;

	////////////////////////////////////////////////////////////
	/// \brief Get advance part of glyph metrics of the UNICODE char
	///
	/// \param[in] ch UNICODE char to get the glyph metrics for
	///
	/// \returns Advance offset into
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC38
	/// \see http://freetype.sourceforge.net/freetype2/docs/tutorial/step2.html
	///
	////////////////////////////////////////////////////////////
	int GetGlyphAdvance(Uint16 ch) const;

	///@}

	///@{
	/// \name Attributes: text metrics

	////////////////////////////////////////////////////////////
	/// \brief Calculate the resulting surface size of the LATIN1 encoded text rendered using font
	///
	/// \param[in] text String to size up
	///
	/// \returns Point representing dimensions of the rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// No actual rendering is done, however correct kerning is done
	/// to get the actual width. The height returned in h is the same
	/// as you can get using GetHeight()
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC39
	///
	////////////////////////////////////////////////////////////
	Point GetSizeText(const std::string& text) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate the resulting surface size of the UTF8 encoded text rendered using font
	///
	/// \param[in] text UTF8 encoded string to size up
	///
	/// \returns Point representing dimensions of the rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// No actual rendering is done, however correct kerning is done
	/// to get the actual width. The height returned in h is the same
	/// as you can get using GetHeight()
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC40
	///
	////////////////////////////////////////////////////////////
	Point GetSizeUTF8(const std::string& text) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate the resulting surface size of the UNICODE encoded text rendered using font
	///
	/// \param[in] text UNICODE null terminated string to size up
	///
	/// \returns Point representing dimensions of the rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// No actual rendering is done, however correct kerning is done
	/// to get the actual width. The height returned in h is the same
	/// as you can get using GetHeight()
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC41
	///
	////////////////////////////////////////////////////////////
	Point GetSizeUNICODE(const Uint16* text) const;

	////////////////////////////////////////////////////////////
	/// \brief Calculate the resulting surface size of the UNICODE encoded text rendered using font
	///
	/// \param[in] text UNICODE null terminated string to size up
	///
	/// \returns Point representing dimensions of the rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// No actual rendering is done, however correct kerning is done
	/// to get the actual width. The height returned in h is the same
	/// as you can get using GetHeight()
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC41
	///
	////////////////////////////////////////////////////////////
	Point GetSizeUNICODE(const std::u16string& text) const;

	///@}

	///@{
	/// \name Rendering: solid

	////////////////////////////////////////////////////////////
	/// \brief Render LATIN1 text using solid mode
	///
	/// \param[in] text LATIN1 string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC43
	///
	////////////////////////////////////////////////////////////
	Surface RenderText_Solid(const std::string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UTF8 text using solid mode
	///
	/// \param[in] text UTF8 string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC44
	///
	////////////////////////////////////////////////////////////
	Surface RenderUTF8_Solid(const std::string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using solid mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC45
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Solid(const Uint16* text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using solid mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC45
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Solid(const std::u16string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render the glyph for UNICODE character using solid mode
	///
	/// \param[in] ch UNICODE character to render
	/// \param[in] fg Color to render the glyph in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC46
	///
	////////////////////////////////////////////////////////////
	Surface RenderGlyph_Solid(Uint16 ch, SDL_Color fg);

	///@}

	///@{
	/// \name Rendering: shaded

	////////////////////////////////////////////////////////////
	/// \brief Render LATIN1 text using shaded mode
	///
	/// \param[in] text LATIN1 string to render
	/// \param[in] fg Color to render the text in
	/// \param[in] bg Color to render the background box in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC47
	///
	////////////////////////////////////////////////////////////
	Surface RenderText_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg);

	////////////////////////////////////////////////////////////
	/// \brief Render UTF8 text using shaded mode
	///
	/// \param[in] text UTF8 string to render
	/// \param[in] fg Color to render the text in
	/// \param[in] bg Color to render the background box in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC48
	///
	////////////////////////////////////////////////////////////
	Surface RenderUTF8_Shaded(const std::string& text, SDL_Color fg, SDL_Color bg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using shaded mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	/// \param[in] bg Color to render the background box in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC49
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Shaded(const Uint16* text, SDL_Color fg, SDL_Color bg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using shaded mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	/// \param[in] bg Color to render the background box in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC49
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Shaded(const std::u16string& text, SDL_Color fg, SDL_Color bg);

	////////////////////////////////////////////////////////////
	/// \brief Render the glyph for UNICODE character using shaded mode
	///
	/// \param[in] ch UNICODE character to render
	/// \param[in] fg Color to render the glyph in
	/// \param[in] bg Color to render the background box in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC50
	///
	////////////////////////////////////////////////////////////
	Surface RenderGlyph_Shaded(Uint16 ch, SDL_Color fg, SDL_Color bg);

	///@}

	///@{
	/// \name Rendering: blended

	////////////////////////////////////////////////////////////
	/// \brief Render LATIN1 text using blended mode
	///
	/// \param[in] text LATIN1 string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC51
	///
	////////////////////////////////////////////////////////////
	Surface RenderText_Blended(const std::string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UTF8 text using blended mode
	///
	/// \param[in] text UTF8 string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC52
	///
	////////////////////////////////////////////////////////////
	Surface RenderUTF8_Blended(const std::string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using blended mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC53
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Blended(const Uint16* text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render UNICODE encoded text using blended mode
	///
	/// \param[in] text UNICODE encoded string to render
	/// \param[in] fg Color to render the text in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC53
	///
	////////////////////////////////////////////////////////////
	Surface RenderUNICODE_Blended(const std::u16string& text, SDL_Color fg);

	////////////////////////////////////////////////////////////
	/// \brief Render the glyph for UNICODE character using blended mode
	///
	/// \param[in] ch UNICODE character to render
	/// \param[in] fg Color to render the glyph in
	///
	/// \returns Surface containing rendered text
	///
	/// \throws SDL2pp::Exception
	///
	/// \see https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC54
	///
	////////////////////////////////////////////////////////////
	Surface RenderGlyph_Blended(Uint16 ch, SDL_Color fg);

	///@}
};

}

#endif
