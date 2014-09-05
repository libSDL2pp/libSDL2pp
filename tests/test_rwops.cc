#include <vector>

#include <SDL2pp/Exception.hh>
#include <SDL2pp/ExtraRWops.hh>
#include <SDL2pp/RWops.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST()
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
			// Seeks
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);
			EXPECT_TRUE(rw.Tell() == 0);
			EXPECT_TRUE(rw.Seek(1, SEEK_SET) == 1);
			EXPECT_TRUE(rw.Tell() == 1);
			EXPECT_TRUE(rw.Seek(1, SEEK_CUR) == 2);
			EXPECT_TRUE(rw.Tell() == 2);
			EXPECT_TRUE(rw.Seek(-1, SEEK_END) == 3);
			EXPECT_TRUE(rw.Tell() == 3);
		}

		{
			// Read via C++
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(rw.Read(buf, 1, 4) == 4);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
		}

		{
			// Read via C++
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(rw.Read(buf, 4, 1) == 1);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
		}

		{
			// Read via SDL
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 1, 4) == 4);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
		}

		{
			// Overread
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[6] = {0};
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 3, 2) == 1);
			rw.Seek(0, SEEK_SET);
			EXPECT_TRUE(SDL_RWread(rw.Get(), buf, 2, 3) == 2);
		}

		{
			// Write
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[2] = {'1', '2'};
			EXPECT_TRUE(rw.Write(buf, 1, 2) == 2);
			EXPECT_TRUE(rw.Write(buf, 2, 1) == 1);
			EXPECT_TRUE(SDL_RWwrite(rw.Get(), buf, 1, 2) == 2);
			EXPECT_TRUE(SDL_RWwrite(rw.Get(), buf, 2, 1) == 1);

			EXPECT_TRUE(rw.Tell() == 8);
			EXPECT_TRUE(buffer.size() == 8);
			EXPECT_TRUE(buffer == std::vector<char>({'1', '2', '1', '2', '1', '2', '1', '2'}));
		}

		{
			// Write past EOF
			char buf[2] = {'x', 'y'};
			EXPECT_TRUE(rw.Seek(100, SEEK_SET) == 100);

			EXPECT_TRUE(rw.Write(buf, 1, 2) == 2);
			EXPECT_TRUE(rw.Tell() == 102);
			EXPECT_TRUE(buffer.size() == 102);
			EXPECT_TRUE(buffer[99] == '\0');
			EXPECT_TRUE(buffer[100] == 'x');
			EXPECT_TRUE(buffer[101] == 'y');
		}

		{
			// Test moving
			RWops rw1(std::move(rw));
			rw1.Close();
		}
	}

	// Short test for ContainerRWops
	{
		const std::vector<char> buffer = { 'a', 'b', 'c', 'd' };

		RWops rw((ConstContainerRWops<std::vector<char>>(buffer)));

		{
			// Read via C++
			EXPECT_TRUE(rw.Seek(0, SEEK_SET) == 0);

			char buf[4] = {0};
			EXPECT_TRUE(rw.Read(buf, 1, 4) == 4);
			EXPECT_TRUE(buf[0] == 'a' && buf[3] == 'd');

			// Position after read
			EXPECT_TRUE(rw.Tell() == 4);
		}

		{
			// Write
			char buf[4] = {0};

			EXPECT_TRUE(rw.Write(buf, 1, 4) == 0);
			EXPECT_TRUE(rw.Write(buf, 4, 1) == 0);
		}
	}

	// SDL file read test
	{
		RWops rw = RWops::FromFile(TESTDATA_DIR "/test.txt");

		EXPECT_TRUE(rw.Tell() == 0);
		char buf[8] = {0};
		EXPECT_TRUE(rw.Read(buf, 1, 8) == 8);
		EXPECT_TRUE(buf[0] == 'a');
		EXPECT_TRUE(buf[7] == 'h');
		EXPECT_TRUE(rw.Tell() == 8);

		rw.Close();
	}
HANDLE_EXCEPTION(Exception& e)
	std::cerr << "unexpected SDL exception was thrown during the test: " << e.what() << ": " << e.GetSDLError() << std::endl;
END_TEST()
