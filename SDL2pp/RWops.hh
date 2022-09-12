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

#ifndef SDL2PP_RWOPS_HH
#define SDL2PP_RWOPS_HH

#include <string>

#include <SDL_rwops.h>
#include <SDL2pp/Exception.hh>
#include <SDL2pp/Export.hh>

namespace SDL2pp {

////////////////////////////////////////////////////////////
/// \brief Base class for custom RWops
///
/// \ingroup io
///
/// \headerfile SDL2pp/RWops.hh
///
/// Derive from this class and override 4 virtual methods used
/// to Seek, Read, Write and Close the data stream.
/// The derived class is expected to be moved-into RWops via
/// RWops(C&& custom_rwops).
///
/// \see SDL2pp::ContainerRWops, SDL2pp::StreamRWops
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT CustomRWops {
public:
	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	virtual ~CustomRWops() {}

	////////////////////////////////////////////////////////////
	/// \brief Get the size of the data stream
	///
	/// \returns Size of the data stream on success, -1 if unknown
	///
	/// \see http://wiki.libsdl.org/SDL_RWsize
	///
	////////////////////////////////////////////////////////////
	virtual Sint64 Size() = 0;

	////////////////////////////////////////////////////////////
	/// \brief Seek within the data stream
	///
	/// \param[in] offset Offset in bytes, relative to whence location; can
	///                   be negative
	/// \param[in] whence Any of RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
	///
	/// \returns Final offset in the data stream after the seek or -1 on error
	///
	/// \see http://wiki.libsdl.org/SDL_RWseek
	///
	////////////////////////////////////////////////////////////
	virtual Sint64 Seek(Sint64 offset, int whence) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Read from a data stream
	///
	/// \param[in] ptr Pointer to a buffer to read data into
	/// \param[in] size Size of each object to read, in bytes
	/// \param[in] maxnum Maximum number of objects to be read
	///
	/// \returns Number of objects read, or 0 at error or end of file
	///
	/// \see http://wiki.libsdl.org/SDL_RWread
	///
	////////////////////////////////////////////////////////////

	virtual size_t Read(void* ptr, size_t size, size_t maxnum) = 0;
	////////////////////////////////////////////////////////////
	/// \brief Write to a data stream
	///
	/// \param[in] ptr Pointer to a buffer containing data to write
	/// \param[in] size Size of each object to write, in bytes
	/// \param[in] num Maximum number of objects to be write
	///
	/// \returns Number of objects written, which will be less than num on error
	///
	/// \see http://wiki.libsdl.org/SDL_RWwrite
	///
	////////////////////////////////////////////////////////////
	virtual size_t Write(const void* ptr, size_t size, size_t num) = 0;

	////////////////////////////////////////////////////////////
	/// \brief Close data source
	///
	/// \returns 0 on success or a negative error code on failure
	///
	/// \see http://wiki.libsdl.org/SDL_RWclose
	///
	////////////////////////////////////////////////////////////
	virtual int Close() = 0;
};

////////////////////////////////////////////////////////////
/// \brief I/O abstraction
///
/// \ingroup io
///
/// \headerfile SDL2pp/RWops.hh
///
/// %RWops is an SDL2 abstraction of file-like I/O. For most functions
/// that take file name as a parameter, SDL2 has an alternative which
/// take %RWops, and through %RWops its functionality is extended from
/// just files to arbitrary objects that support file-like operations.
///
/// For example, SDL2 provide 4 builtin types of %RWops: File (takes
/// file name and works with plain file), FP (takes stdio's FILE* and
/// works with it), Mem and ConstMem (take memory chunk and work with
/// it like a file) and allow one to write custom RWops.
///
/// SDL2pp::RWops support all this in extended C++ way.
///
/// Usage example:
/// \code
/// {
///     // RWops which work on a plain file
///     SDL2pp::RWops ops = SDL2pp::RWops::FromFile("myfile.txt");
///
///     // Texture is loaded through RWops
///     SDL2pp::Texture(ops);
/// }
/// \endcode
///
/// Implementation note:
///
/// This class is more complicated than just wrapper over SDL_RWops,
/// but it's needed to both retain compatibility with C SDL2 and to
/// make it possible to write pure C++ %RWops classes, in a safe way.
///
////////////////////////////////////////////////////////////
class SDL2PP_EXPORT RWops {
protected:
	SDL_RWops* rwops_; ///< Managed SDL_RWops object

private:
	static Sint64 StdSizeFuncWrapper(SDL_RWops* context);
	static Sint64 StdSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence);
	static size_t StdReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum);
	static size_t StdWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum);
	static int StdCloseFuncWrapper(SDL_RWops* context);

	static Sint64 CustomSizeFuncWrapper(SDL_RWops* context);
	static Sint64 CustomSeekFuncWrapper(SDL_RWops* context, Sint64 offset, int whence);
	static size_t CustomReadFuncWrapper(SDL_RWops* context, void *ptr, size_t size, size_t maxnum);
	static size_t CustomWriteFuncWrapper(SDL_RWops* context, const void *ptr, size_t size, size_t maxnum);
	static int CustomCloseFuncWrapper(SDL_RWops* context);

	static RWops CheckedCreateStandardRWops(SDL_RWops* sdl_rwops, const char* errmsg);

public:
	////////////////////////////////////////////////////////////
	/// \brief Create RWops working through stdio's FILE*
	///
	/// \param[in] file Pointer to stdio's FILE type
	/// \param[in] autoclose True to take ownership of given FILE and
	///                      close it on RWops destruction
	///
	/// \returns Created RWops
	///
	/// \see http://wiki.libsdl.org/SDL_RWFromFP
	///
	////////////////////////////////////////////////////////////
	static RWops FromFP(FILE* file, bool autoclose);

	////////////////////////////////////////////////////////////
	/// \brief Create RWops working with a constant memory chunk
	///
	/// \param[in] mem Pointer to the memory to work with
	/// \param[in] size Size of a memory chunk
	///
	/// \returns Created RWops
	///
	/// \see http://wiki.libsdl.org/SDL_RWFromConstMem
	///
	////////////////////////////////////////////////////////////
	static RWops FromConstMem(const void* mem, int size);

	////////////////////////////////////////////////////////////
	/// \brief Create RWops working with a memory chunk
	///
	/// \param[in] mem Pointer to the memory to work with
	/// \param[in] size Size of a memory chunk
	///
	/// \returns Created RWops
	///
	/// \see http://wiki.libsdl.org/SDL_RWFromMem
	///
	////////////////////////////////////////////////////////////
	static RWops FromMem(void* mem, int size);

	////////////////////////////////////////////////////////////
	/// \brief Create RWops working with plain file
	///
	/// \param[in] file Path to file
	/// \param[in] mode Open mode in stdio way
	///
	/// \returns Created RWops
	///
	/// \see http://wiki.libsdl.org/SDL_RWFromFile
	///
	////////////////////////////////////////////////////////////
	static RWops FromFile(const std::string& file, const std::string& mode = "rb");

	////////////////////////////////////////////////////////////
	/// \brief Create RWops from existing SDL2 SDL_RWops structure
	///
	/// \param[in] rwops Pointer to SDL_RWops to use
	///
	////////////////////////////////////////////////////////////
	explicit RWops(SDL_RWops* rwops);

	////////////////////////////////////////////////////////////
	/// \brief Move constructor
	///
	/// \param[in] other SDL2pp::RWops to move data from
	///
	////////////////////////////////////////////////////////////
	RWops(RWops&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Move assignment operator
	///
	/// \param[in] other SDL2pp::RWops to move data from
	///
	/// \returns Reference to self
	///
	////////////////////////////////////////////////////////////
	RWops& operator=(RWops&& other) noexcept;

	////////////////////////////////////////////////////////////
	/// \brief Deleted copy constructor
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	RWops(const RWops&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Deleted assignment operator
	///
	/// This class is not copyable
	///
	////////////////////////////////////////////////////////////
	RWops& operator=(const RWops&) = delete;

	////////////////////////////////////////////////////////////
	/// \brief Create RWops from CustomRWops derived class
	///
	/// \param[in] custom_rwops Custom %RWops functions
	///
	/// \throws SDL2pp::Exception
	///
	/// \todo make this take arguments for C constructor
	///
	////////////////////////////////////////////////////////////
	template<class C>
	explicit RWops(C&& custom_rwops) {
		rwops_ = SDL_AllocRW();
		if (rwops_ == nullptr)
			throw Exception("SDL_AllocRW");

		rwops_->size = CustomSizeFuncWrapper;
		rwops_->seek = CustomSeekFuncWrapper;
		rwops_->read = CustomReadFuncWrapper;
		rwops_->write = CustomWriteFuncWrapper;
		rwops_->close = CustomCloseFuncWrapper;
		rwops_->type = 0x57524370; // "pCRW" for libSDLp[p] [C]ustom [RW]ops
		try {
			rwops_->hidden.unknown.data1 = static_cast<void*>(new C(std::move(custom_rwops)));
		} catch (...) {
			SDL_FreeRW(rwops_);
			throw;
		}
		rwops_->hidden.unknown.data2 = static_cast<void*>(this);
	}

	////////////////////////////////////////////////////////////
	/// \brief Destructor
	///
	////////////////////////////////////////////////////////////
	~RWops();

	////////////////////////////////////////////////////////////
	/// \brief Get pointer to managed SDL_RWops structure
	///
	/// \returns Pointer to managed SDL_RWops structure
	///
	////////////////////////////////////////////////////////////
	SDL_RWops* Get() const;

	////////////////////////////////////////////////////////////
	/// \brief Close data source
	///
	/// \returns 0 on success or a negative error code on failure
	///
	/// \see http://wiki.libsdl.org/SDL_RWclose
	///
	////////////////////////////////////////////////////////////
	int Close();

	////////////////////////////////////////////////////////////
	/// \brief Read from a data stream
	///
	/// \param[in] ptr Pointer to a buffer to read data into
	/// \param[in] size Size of each object to read, in bytes
	/// \param[in] maxnum Maximum number of objects to be read
	///
	/// \returns Number of objects read, or 0 at error or end of file
	///
	/// \see http://wiki.libsdl.org/SDL_RWread
	///
	////////////////////////////////////////////////////////////
	size_t Read(void* ptr, size_t size, size_t maxnum);

	////////////////////////////////////////////////////////////
	/// \brief Seek within the data stream
	///
	/// \param[in] offset Offset in bytes, relative to whence location; can
	///                   be negative
	/// \param[in] whence Any of RW_SEEK_SET, RW_SEEK_CUR, RW_SEEK_END
	///
	/// \returns Final offset in the data stream after the seek or -1 on error
	///
	/// \see http://wiki.libsdl.org/SDL_RWseek
	///
	////////////////////////////////////////////////////////////
	Sint64 Seek(Sint64 offset, int whence);

	////////////////////////////////////////////////////////////
	/// \brief Write to a data stream
	///
	/// \param[in] ptr Pointer to a buffer containing data to write
	/// \param[in] size Size of each object to write, in bytes
	/// \param[in] num Number of objects to be write
	///
	/// \returns Number of objects written, which will be less than num on error
	///
	/// \see http://wiki.libsdl.org/SDL_RWwrite
	///
	////////////////////////////////////////////////////////////
	size_t Write(const void* ptr, size_t size, size_t num);

	////////////////////////////////////////////////////////////
	/// \brief Determine the current read/write offset within the data stream
	///
	/// \returns Current offset in the stream, or -1 if the information can not be determined
	///
	/// \see http://wiki.libsdl.org/SDL_RWtell
	///
	////////////////////////////////////////////////////////////
	Sint64 Tell();

	////////////////////////////////////////////////////////////
	/// \brief Get current size of the data container
	///
	/// \returns Data container size in bytes, or -1 if the information can not be determined
	///
	////////////////////////////////////////////////////////////
	Sint64 Size();

	////////////////////////////////////////////////////////////
	/// \brief Read 16 bits of big-endian data from data stream
	///        and return in native format
	///
	/// \returns 16 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadBE16
	///
	////////////////////////////////////////////////////////////
	Uint16 ReadBE16();

	////////////////////////////////////////////////////////////
	/// \brief Read 32 bits of big-endian data from data stream
	///        and return in native format
	///
	/// \returns 32 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadBE32
	///
	////////////////////////////////////////////////////////////
	Uint32 ReadBE32();

	////////////////////////////////////////////////////////////
	/// \brief Read 64 bits of big-endian data from data stream
	///        and return in native format
	///
	/// \returns 64 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadBE64
	///
	////////////////////////////////////////////////////////////
	Uint64 ReadBE64();

	////////////////////////////////////////////////////////////
	/// \brief Read 16 bits of little-endian data from data stream
	///        and return in native format
	///
	/// \returns 16 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadLE16
	///
	////////////////////////////////////////////////////////////
	Uint16 ReadLE16();

	////////////////////////////////////////////////////////////
	/// \brief Read 32 bits of little-endian data from data stream
	///        and return in native format
	///
	/// \returns 32 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadLE32
	///
	////////////////////////////////////////////////////////////
	Uint32 ReadLE32();

	////////////////////////////////////////////////////////////
	/// \brief Read 64 bits of little-endian data from data stream
	///        and return in native format
	///
	/// \returns 64 bits of data in the native byte order
	///
	/// \see http://wiki.libsdl.org/SDL_ReadLE64
	///
	////////////////////////////////////////////////////////////
	Uint64 ReadLE64();

	////////////////////////////////////////////////////////////
	/// \brief Write 16 bits in native format to a data stream
	///        as big-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteBE16
	///
	////////////////////////////////////////////////////////////
	size_t WriteBE16(Uint16 value);

	////////////////////////////////////////////////////////////
	/// \brief Write 32 bits in native format to a data stream
	///        as big-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteBE32
	///
	////////////////////////////////////////////////////////////
	size_t WriteBE32(Uint32 value);

	////////////////////////////////////////////////////////////
	/// \brief Write 64 bits in native format to a data stream
	///        as big-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteBE64
	///
	////////////////////////////////////////////////////////////
	size_t WriteBE64(Uint64 value);

	////////////////////////////////////////////////////////////
	/// \brief Write 16 bits in native format to a data stream
	///        as little-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteLE16
	///
	////////////////////////////////////////////////////////////
	size_t WriteLE16(Uint16 value);

	////////////////////////////////////////////////////////////
	/// \brief Write 32 bits in native format to a data stream
	///        as little-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteLE32
	///
	////////////////////////////////////////////////////////////
	size_t WriteLE32(Uint32 value);

	////////////////////////////////////////////////////////////
	/// \brief Write 64 bits in native format to a data stream
	///        as little-endian data
	///
	/// \param[in] value Data to be written, in native format
	///
	/// \returns 1 on successful write, 0 on error
	///
	/// \see http://wiki.libsdl.org/SDL_WriteLE64
	///
	////////////////////////////////////////////////////////////
	size_t WriteLE64(Uint64 value);
};

}

#endif
