#include <vector>

#include <SDL_main.h>

#include <SDL2pp/Exception.hh>
#include <SDL2pp/ContainerRWops.hh>
#include <SDL2pp/StreamRWops.hh>
#include <SDL2pp/RWops.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	// First check our custom ContainerRWops, not touching
	// SDL-provided RWops services
	{
		std::vector<char> buffer = { 'a', 'b', 'c', 'd' };

		RWops rw((ContainerRWops<std::vector<char>>(buffer)));

		{
			// Initial position
			EXPECT_TRUE(rw.Tell() == 0);
		}

		{
			// Size
			EXPECT_TRUE(rw.Size() == 4);
		}

		{
			// Seeks
			EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);
			EXPECT_TRUE(rw.Tell() == 0);
			EXPECT_TRUE(rw.Seek(1, RW_SEEK_SET) == 1);
			EXPECT_TRUE(rw.Tell() == 1);
			EXPECT_TRUE(rw.Seek(1, RW_SEEK_CUR) == 2);
			EXPECT_TRUE(rw.Tell() == 2);
			EXPECT_TRUE(rw.Seek(-1, RW_SEEK_END) == 3);
			EXPECT_TRUE(rw.Tell() == 3);
		}

		{
			// Read via C++
			EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(rw.Read(buf, 1, 4) == 4);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
		}

		{
			// Read via C++
			EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(rw.Read(buf, 4, 1) == 1);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
			EXPECT_TRUE(rw.Size() == 4);
		}

		{
			// Read via SDL
			EXPECT_TRUE(SDL_RWseek(rw.Get(), 0, RW_SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 1, 4) == 4);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(SDL_RWtell(rw.Get()) == 4);
			EXPECT_TRUE(SDL_RWsize(rw.Get()) == 4);
		}

		{
			// Overread
			EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);

			char buf[6] = {0};
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 3, 2) == 1);
			rw.Seek(0, RW_SEEK_SET);
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 2, 3) == 2);
		}

		{
			// Write
			EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);

			char buf[2] = {'1', '2'};
			EXPECT_TRUE(rw.Write(buf, 1, 2) == 2);
			EXPECT_TRUE(rw.Write(buf, 2, 1) == 1);
			EXPECT_TRUE(SDL_RWwrite(rw.Get(), buf, 1, 2) == 2);
			EXPECT_TRUE(SDL_RWwrite(rw.Get(), buf, 2, 1) == 1);

			EXPECT_TRUE(rw.Tell() == 8);
			EXPECT_TRUE(buffer.size() == 8);
			EXPECT_TRUE(buffer == std::vector<char>({'1', '2', '1', '2', '1', '2', '1', '2'}));
			EXPECT_TRUE(rw.Size() == 8);
		}

		{
			// Write past EOF
			char buf[2] = {'x', 'y'};
			EXPECT_TRUE(rw.Seek(100, RW_SEEK_SET) == 100);

			EXPECT_TRUE(rw.Write(buf, 1, 2) == 2);
			EXPECT_TRUE(rw.Tell() == 102);
			EXPECT_TRUE(buffer.size() == 102);
			EXPECT_TRUE(buffer[99] == '\0');
			EXPECT_TRUE(buffer[100] == 'x');
			EXPECT_TRUE(buffer[101] == 'y');
			EXPECT_TRUE(rw.Size() == 102);
		}

		{
			// Test moving
			RWops rw1(std::move(rw));
			rw1.Close();
		}
	}

	// Short test for ContainerRWops
	{
		{
			const std::vector<char> buffer = { 'a', 'b', 'c', 'd' };

			RWops rw((ContainerRWops<const std::vector<char>>(buffer)));

			{
				// Read via C++
				EXPECT_TRUE(rw.Seek(0, RW_SEEK_SET) == 0);

				char buf[4] = {0};
				EXPECT_TRUE(rw.Read(buf, 1, 4) == 4);
				EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

				// Position after read
				EXPECT_TRUE(rw.Tell() == 4);
			}

			{
				// Write to const container fails
				char buf[4] = {0};

				EXPECT_TRUE(rw.Write(buf, 1, 4) == 0);
				EXPECT_TRUE(rw.Write(buf, 4, 1) == 0);
			}
		}

		{
			std::vector<char> vec;

			RWops rw((ContainerRWops<std::vector<char>>(vec)));

			{
				// Write to non-const container
				char buf[4] = {'a', 'b', 'c', 'd'};

				EXPECT_TRUE(rw.Write(buf, 1, 4) == 4);
				EXPECT_TRUE(rw.Write(buf, 4, 1) == 1);

				EXPECT_TRUE(rw.Seek(2, RW_SEEK_SET) == 2);
				EXPECT_TRUE(rw.Write(buf, 2, 2) == 2);

				EXPECT_TRUE(vec.size() == 8);
				EXPECT_TRUE(std::string(vec.data(), 8) == "ababcdcd");
			}
		}
	}

	// Test for StreamRWops
	{
		{
			// write test

			std::stringstream test;
			RWops rw((StreamRWops<std::ostream>(test)));

			EXPECT_EQUAL(rw.Size(), 0);

			char buf[4] = { 'a', 'b', 'c', 'd' };
			EXPECT_TRUE(rw.Write(buf, 1, 4) == 4);

			EXPECT_EQUAL(rw.Size(), 4);

			EXPECT_TRUE(rw.Seek(0, RW_SEEK_CUR) == 4);

			EXPECT_TRUE(rw.Seek(2, RW_SEEK_SET) == 2);

			EXPECT_TRUE(rw.Write(buf, 1, 4) == 4);

			EXPECT_EQUAL(rw.Size(), 6);

			EXPECT_EQUAL(test.str(), "ababcd");
		}

		{
			// read test

			std::stringstream test("abcdef");
			RWops rw((StreamRWops<std::istream>(test)));

			EXPECT_EQUAL(rw.Size(), 6);

			char buf[4];
			EXPECT_EQUAL(rw.Read(buf, 1, 4), 4UL);

			EXPECT_EQUAL(std::string(buf, 4), "abcd");

			EXPECT_EQUAL(rw.Seek(0, RW_SEEK_CUR), 4);

			EXPECT_EQUAL(rw.Seek(2, RW_SEEK_SET), 2);

			EXPECT_EQUAL(rw.Read(buf, 1, 4), 4UL);

			EXPECT_EQUAL(std::string(buf, 4), "cdef");

			// short read
			EXPECT_EQUAL(rw.Seek(4, RW_SEEK_SET), 4);

			EXPECT_EQUAL(rw.Read(buf, 1, 4), 2UL);

			EXPECT_EQUAL(std::string(buf, 2), "ef");

			// short object read
			EXPECT_EQUAL(rw.Seek(4, RW_SEEK_SET), 4);

			EXPECT_EQUAL(rw.Read(buf, 4, 1), 0UL);

			EXPECT_EQUAL(rw.Seek(0, RW_SEEK_CUR), 4);

			// read end
			EXPECT_EQUAL(rw.Read(buf, 1, 2), 2UL);

			EXPECT_EQUAL(std::string(buf, 2), "ef");

			EXPECT_EQUAL(rw.Size(), 6);
		}
	}

	// SDL file read test
	{
		RWops rw = RWops::FromFile(TESTDATA_DIR "/test.txt");

		EXPECT_TRUE(rw.Tell() == 0);
		EXPECT_TRUE(rw.Size() == 9);
		char buf[8] = {0};
		EXPECT_TRUE(rw.Read(buf, 1, 8) == 8);
		EXPECT_TRUE(buf[0] == 'a');
		EXPECT_TRUE(buf[7] == 'h');
		EXPECT_TRUE(rw.Tell() == 8);
		EXPECT_TRUE(rw.Size() == 9);

		rw.Close();
	}

	// Fixed width reads/writes
	{
		std::vector<char> data, outdata;
		for (int i = 0; i < 28; i++)
			data.push_back(i);

		RWops rw((ContainerRWops<std::vector<char>>(data)));

		EXPECT_EQUAL(rw.ReadBE16(), 0x0001U);
		EXPECT_EQUAL(rw.ReadLE16(), 0x0302U);
		EXPECT_EQUAL(rw.ReadBE32(), 0x04050607U);
		EXPECT_EQUAL(rw.ReadLE32(), 0x0B0A0908U);
		EXPECT_EQUAL(rw.ReadBE64(), 0x0C0D0E0F10111213ULL);
		EXPECT_EQUAL(rw.ReadLE64(), 0x1B1A191817161514ULL);

		RWops rw1((ContainerRWops<std::vector<char>>(outdata)));

		EXPECT_EQUAL(rw1.WriteBE16(0x0001U), 1U);
		EXPECT_EQUAL(rw1.WriteLE16(0x0302U), 1U);
		EXPECT_EQUAL(rw1.WriteBE32(0x04050607U), 1U);
		EXPECT_EQUAL(rw1.WriteLE32(0x0B0A0908U), 1U);
		EXPECT_EQUAL(rw1.WriteBE64(0x0C0D0E0F10111213ULL), 1U);
		EXPECT_EQUAL(rw1.WriteLE64(0x1B1A191817161514ULL), 1U);

		EXPECT_EQUAL(data.size(), outdata.size());

		EXPECT_TRUE(data == outdata);
	}

HANDLE_EXCEPTION(Exception& e)
	std::cerr << "unexpected SDL exception was thrown during the test: " << e.what() << ": " << e.GetSDLError() << std::endl;
END_TEST()
