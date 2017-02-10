#include <SDL_main.h>

#include <SDL2pp/Point.hh>
#include <SDL2pp/Rect.hh>

#include "testing.h"

using namespace SDL2pp;

BEGIN_TEST(int, char*[])
	{
		// Point basic ops
		Point p(1,2);

		EXPECT_TRUE(p.GetX() == 1 && p.GetY() == 2);
		EXPECT_TRUE(p == Point(1,2));
		EXPECT_TRUE(p != Point(1,1));
		EXPECT_TRUE(p != Point(2,2));
		EXPECT_TRUE(p.x == 1);
		EXPECT_TRUE(p.y == 2);

		p.SetX(4);
		p.SetY(5);

		EXPECT_TRUE(p.GetX() == 4 && p.GetY() == 5);
		EXPECT_TRUE(p == Point(4,5));
		EXPECT_TRUE(p.x == 4);
		EXPECT_TRUE(p.y == 5);

		p = Point(6,7);

		EXPECT_TRUE(p.GetX() == 6 && p.GetY() == 7);
		EXPECT_TRUE(p == Point(6,7));
		EXPECT_TRUE(p.x == 6);
		EXPECT_TRUE(p.y == 7);
	}

	{
		// Point self assignment
		Point p(8,9);
		p = Point(10,11);

		p = p;

		EXPECT_TRUE(p.GetX() == 10 && p.GetY() == 11);
	}

	{
		// Point self move-assignment
		Point p(12,13);
		p = Point(14,15);

		Point& pref = p;
		p = std::move(pref);

		EXPECT_TRUE(p.GetX() == 14 && p.GetY() == 15);
	}

	{
		// Point arith

		// Unary
		EXPECT_EQUAL(-Point(1, 2), Point(-1, -2));

		// Binary
		EXPECT_EQUAL(Point(1, 2) + Point(10, 20), Point(11, 22));
		EXPECT_EQUAL(Point(-1, -2) - Point(10, 20), Point(-11, -22));
		EXPECT_EQUAL(Point(20, 60) / 5, Point(4, 12));
		EXPECT_EQUAL(Point(20, 60) / Point(5, 10), Point(4, 6));
		EXPECT_EQUAL(Point(20, 60) % 11, Point(9, 5));
		EXPECT_EQUAL(Point(20, 60) % Point(11, 13), Point(9, 8));
		EXPECT_EQUAL(Point(2, 3) * 5, Point(10, 15));
		EXPECT_EQUAL(Point(2, 3) * Point(10, 20), Point(20, 60));

		// Assignments
		Point p(1, 2);
		EXPECT_EQUAL(p += Point(10, 20), Point(11, 22));
		EXPECT_EQUAL(p -= Point(1, 2), Point(10, 20));
		EXPECT_EQUAL(p /= 2, Point(5, 10));
		EXPECT_EQUAL(p %= 7, Point(5, 3));
		EXPECT_EQUAL(p *= 3, Point(15, 9));
		EXPECT_EQUAL(p /= Point(5, 3), Point(3, 3));
		EXPECT_EQUAL(p *= Point(10, 20), Point(30, 60));
		EXPECT_EQUAL(p %= Point(7, 11), Point(2, 5));

		// Less-than
		EXPECT_TRUE(Point(0, 0) < Point(1, 0));
		EXPECT_TRUE(Point(0, 1) < Point(1, 0));
		EXPECT_TRUE(Point(0, 1) < Point(1, 1));
		EXPECT_TRUE(Point(0, 0) < Point(0, 1));

		EXPECT_TRUE(!(Point(1, 0) < Point(0, 0)));
		EXPECT_TRUE(!(Point(1, 0) < Point(0, 1)));
		EXPECT_TRUE(!(Point(1, 1) < Point(0, 1)));
		EXPECT_TRUE(!(Point(0, 1) < Point(0, 0)));
		EXPECT_TRUE(!(Point(1, 1) < Point(1, 1)));

		// Hashes
		EXPECT_TRUE(std::hash<Point>()(Point(123, 456)) == std::hash<Point>()(Point(123, 456)));
		EXPECT_TRUE(std::hash<Point>()(Point(0, 0)) != std::hash<Point>()(Point(0, 1)));
		EXPECT_TRUE(std::hash<Point>()(Point(0, 0)) != std::hash<Point>()(Point(1, 0)));
		EXPECT_TRUE(std::hash<Point>()(Point(1, 0)) != std::hash<Point>()(Point(0, 1)));
	}

	{
		// Rect basic ops
		Rect r(1,2,3,4);

		EXPECT_TRUE(r.GetX() == 1 && r.GetY() == 2 && r.GetW() == 3 && r.GetH() == 4);
		EXPECT_TRUE(r == Rect(1,2,3,4));
		EXPECT_TRUE(r != Rect(2,2,3,4));
		EXPECT_TRUE(r != Rect(1,3,3,4));
		EXPECT_TRUE(r != Rect(1,2,4,4));
		EXPECT_TRUE(r != Rect(1,2,3,5));
		EXPECT_TRUE(r.x == 1 && r.y == 2 && r.w == 3 && r.h == 4);

		r.SetX(5);
		r.SetY(6);
		r.SetW(7);
		r.SetH(8);

		EXPECT_TRUE(r.GetX() == 5 && r.GetY() == 6 && r.GetW() == 7 && r.GetH() == 8);
		EXPECT_TRUE(r == Rect(5,6,7,8));
		EXPECT_TRUE(r.x == 5 && r.y == 6 && r.w == 7 && r.h == 8);

		r = Rect(9,10,11,12);

		EXPECT_TRUE(r.GetX() == 9 && r.GetY() == 10 && r.GetW() == 11 && r.GetH() == 12);
		EXPECT_TRUE(r == Rect(9,10,11,12));
		EXPECT_TRUE(r.x == 9 && r.y == 10 && r.w == 11 && r.h == 12);
	}

	{
		// Rect self assignment
		Rect r(13,14,15,16);
		r = Rect(17,18,19,20);

		r = r;

		EXPECT_TRUE(r.GetX() == 17 && r.GetY() == 18 && r.GetW() == 19 && r.GetH() == 20);
	}

	{
		// Rect self move assignment
		Rect r(21,22,23,24);
		r = Rect(25,26,27,28);

		Rect& rref = r;
		r = std::move(rref);

		EXPECT_TRUE(r.GetX() == 25 && r.GetY() == 26 && r.GetW() == 27 && r.GetH() == 28);
	}

	{
		// Rect second point stuff
		Rect r(50,100,5,10);

		EXPECT_TRUE(r.GetX2() == 54 && r.GetY2() == 109);

		r.SetX2(50+15);
		r.SetY2(100+30);

		EXPECT_TRUE(r.GetW() == 16 && r.GetH() == 31);
	}

	{
		// Constructors
		EXPECT_EQUAL(Rect::FromCenter(100, 100, 5, 7), Rect(98, 97, 5, 7));
		EXPECT_EQUAL(Rect::FromCenter(Point(100, 100), Point(5, 7)), Rect(98, 97, 5, 7));

		EXPECT_EQUAL(Rect::FromCorners(10, 20, 30, 40), Rect(10, 20, 21, 21));
		EXPECT_EQUAL(Rect::FromCorners(Point(10, 20), Point(30, 40)), Rect(10, 20, 21, 21));
	}

	{
		// Rect contains point
		Rect r(10, 20, 5, 5);

		EXPECT_TRUE(r.Contains(Point(10, 20)));
		EXPECT_TRUE(r.Contains(Point(14, 24)));

		EXPECT_TRUE(!r.Contains(Point(9, 20)));
		EXPECT_TRUE(!r.Contains(Point(10, 19)));
		EXPECT_TRUE(!r.Contains(Point(15, 20)));
		EXPECT_TRUE(!r.Contains(Point(10, 25)));

		EXPECT_TRUE(r.Contains(10, 20));
		EXPECT_TRUE(r.Contains(14, 24));

		EXPECT_TRUE(!r.Contains(9, 20));
		EXPECT_TRUE(!r.Contains(10, 19));
		EXPECT_TRUE(!r.Contains(15, 20));
		EXPECT_TRUE(!r.Contains(10, 25));

		// Rect contains rect
		EXPECT_TRUE(r.Contains(r));
		EXPECT_TRUE(r.Contains(Rect(11, 21, 3, 3)));

		EXPECT_TRUE(!r.Contains(Rect(9, 20, 5, 5)));
		EXPECT_TRUE(!r.Contains(Rect(10, 19, 5, 5)));
		EXPECT_TRUE(!r.Contains(Rect(10, 20, 6, 5)));
		EXPECT_TRUE(!r.Contains(Rect(10, 20, 5, 6)));
	}

	{
		// Rect intersections
		// test both GetIntersection() and Intersects() as the former uses the latter
		Rect rect(10, 20, 30, 40);

		EXPECT_TRUE(rect.Intersects(rect));
		EXPECT_TRUE(rect.GetIntersection(rect) == rect);

		// simple intersection
		EXPECT_TRUE(rect.GetIntersection(Rect(5, 15, 30, 40)) == Rect(10, 20, 25, 35));
		EXPECT_TRUE(rect.GetIntersection(Rect(15, 25, 30, 40)) == Rect(15, 25, 25, 35));

		// larger at left
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 0, 10, 80)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 0, 11, 80)) == Rect(10, 20, 1, 40));

		// larger at top
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 0, 50, 20)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 0, 50, 21)) == Rect(10, 20, 30, 1));

		// larger at bottom
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 60, 50, 20)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 59, 50, 20)) == Rect(10, 59, 30, 1));

		// larger at right
		EXPECT_TRUE(rect.GetIntersection(Rect(40, 0, 20, 80)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(39, 0, 20, 80)) == Rect(39, 20, 1, 40));

		// smaller at left
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 30, 10, 20)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 30, 20, 20)) == Rect(10, 30, 10, 20));

		// smaller at top
		EXPECT_TRUE(rect.GetIntersection(Rect(20, 10, 10, 10)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(20, 10, 10, 20)) == Rect(20, 20, 10, 10));

		// smaller at bottom
		EXPECT_TRUE(rect.GetIntersection(Rect(20, 60, 10, 10)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(20, 50, 10, 20)) == Rect(20, 50, 10, 10));

		// smaller at right
		EXPECT_TRUE(rect.GetIntersection(Rect(40, 30, 10, 20)) == NullOpt);
		EXPECT_TRUE(rect.GetIntersection(Rect(30, 30, 20, 20)) == Rect(30, 30, 10, 20));

		// smaller
		EXPECT_TRUE(rect.GetIntersection(Rect(20, 30, 10, 20)) == Rect(20, 30, 10, 20));

		// larger
		EXPECT_TRUE(rect.GetIntersection(Rect(0, 0, 100, 100)) == rect);
	}

	{
		// Rect unions
		EXPECT_EQUAL(Rect(10, 20, 1, 1).GetUnion(Rect(30, 40, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(30, 20, 1, 1).GetUnion(Rect(10, 40, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(10, 40, 1, 1).GetUnion(Rect(30, 20, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(30, 40, 1, 1).GetUnion(Rect(10, 20, 1, 1)), Rect::FromCorners(10, 20, 30, 40));

		EXPECT_EQUAL(Rect(10, 20, 1, 1).Union(Rect(30, 40, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(30, 20, 1, 1).Union(Rect(10, 40, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(10, 40, 1, 1).Union(Rect(30, 20, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(30, 40, 1, 1).Union(Rect(10, 20, 1, 1)), Rect::FromCorners(10, 20, 30, 40));
	}

	{
		// Rect/line intersections
		Rect rect = Rect::FromCorners(10, 10, 20, 20);

		Point p1(0, 0), p2(30, 30);
		EXPECT_TRUE(rect.IntersectLine(p1, p2));
		EXPECT_EQUAL(p1, Point(10, 10));
		EXPECT_EQUAL(p2, Point(20, 20));

		int x1 = 30, y1 = 0, x2 = 0, y2 = 30;
		EXPECT_TRUE(rect.IntersectLine(x1, y1, x2, y2));
		EXPECT_EQUAL(x1, 20);
		EXPECT_EQUAL(y1, 10);
		EXPECT_EQUAL(x2, 10);
		EXPECT_EQUAL(y2, 20);
	}

	{
		// Rect extend
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetExtension(0), Rect(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetExtension(10), Rect(0, 10, 50, 60));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetExtension(10, 20), Rect(0, 0, 50, 80));

		EXPECT_EQUAL(Rect(10, 20, 30, 40).Extend(0), Rect(10, 20, 30, 40));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).Extend(10), Rect(0, 10, 50, 60));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).Extend(10, 20), Rect(0, 0, 50, 80));
	}

	{
		// Rect point getters
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetTopLeft(), Point(10, 20));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetTopRight(), Point(39, 20));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetBottomLeft(), Point(10, 59));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetBottomRight(), Point(39, 59));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetSize(), Point(30, 40));
		EXPECT_EQUAL(Rect(10, 20, 30, 40).GetCentroid(), Point(25, 40));
	}

	{
		// Rect offset
		Rect r(1, 2, 3, 4);

		EXPECT_EQUAL(r + Point(10, 20), Rect(11, 22, 3, 4));
		EXPECT_EQUAL(r - Point(10, 20), Rect(-9, -18, 3, 4));

		r += Point(10, 20);

		EXPECT_EQUAL(r, Rect(11, 22, 3, 4));

		r -= Point(20, 40);

		EXPECT_EQUAL(r, Rect(-9, -18, 3, 4));
	}

	{
		// Less-than
		EXPECT_TRUE(!(Rect(0, 0, 0, 0) < Rect(0, 0, 0, 0)));
		EXPECT_TRUE(Rect(0, 0, 0, 0) < Rect(0, 0, 0, 1));
		EXPECT_TRUE(Rect(0, 0, 0, 0) < Rect(0, 0, 1, 0));
		EXPECT_TRUE(Rect(0, 0, 0, 0) < Rect(0, 1, 0, 0));
		EXPECT_TRUE(Rect(0, 0, 0, 0) < Rect(1, 0, 0, 0));

		EXPECT_TRUE(!(Rect(0, 0, 0, 1) < Rect(0, 0, 0, 0)));
		EXPECT_TRUE(!(Rect(0, 0, 0, 1) < Rect(0, 0, 0, 1)));
		EXPECT_TRUE(Rect(0, 0, 0, 1) < Rect(0, 0, 1, 0));
		EXPECT_TRUE(Rect(0, 0, 0, 1) < Rect(0, 1, 0, 0));
		EXPECT_TRUE(Rect(0, 0, 0, 1) < Rect(1, 0, 0, 0));

		EXPECT_TRUE(!(Rect(0, 0, 1, 0) < Rect(0, 0, 0, 0)));
		EXPECT_TRUE(!(Rect(0, 0, 1, 0) < Rect(0, 0, 0, 1)));
		EXPECT_TRUE(!(Rect(0, 0, 1, 0) < Rect(0, 0, 1, 0)));
		EXPECT_TRUE(Rect(0, 0, 1, 0) < Rect(0, 1, 0, 0));
		EXPECT_TRUE(Rect(0, 0, 1, 0) < Rect(1, 0, 0, 0));

		EXPECT_TRUE(!(Rect(0, 1, 0, 0) < Rect(0, 0, 0, 0)));
		EXPECT_TRUE(!(Rect(0, 1, 0, 0) < Rect(0, 0, 0, 1)));
		EXPECT_TRUE(!(Rect(0, 1, 0, 0) < Rect(0, 0, 1, 0)));
		EXPECT_TRUE(!(Rect(0, 1, 0, 0) < Rect(0, 1, 0, 0)));
		EXPECT_TRUE(Rect(0, 1, 0, 0) < Rect(1, 0, 0, 0));

		EXPECT_TRUE(!(Rect(1, 0, 0, 0) < Rect(0, 0, 0, 0)));
		EXPECT_TRUE(!(Rect(1, 0, 0, 0) < Rect(0, 0, 0, 1)));
		EXPECT_TRUE(!(Rect(1, 0, 0, 0) < Rect(0, 0, 1, 0)));
		EXPECT_TRUE(!(Rect(1, 0, 0, 0) < Rect(0, 1, 0, 0)));
		EXPECT_TRUE(!(Rect(1, 0, 0, 0) < Rect(1, 0, 0, 0)));
	}

	{
		// Hashes
		EXPECT_TRUE(std::hash<Rect>()(Rect(1, 2, 3, 4)) == std::hash<Rect>()(Rect(1, 2, 3, 4)));
		EXPECT_TRUE(std::hash<Rect>()(Rect(1, 2, 3, 4)) != std::hash<Rect>()(Rect(2, 1, 3, 4)));
		EXPECT_TRUE(std::hash<Rect>()(Rect(1, 2, 3, 4)) != std::hash<Rect>()(Rect(1, 2, 4, 3)));
	}

	{
		// Construction from and comparison with SDL objects
		SDL_Rect sdlrect = { 1, 2, 3, 4 };

		SDL_Point sdlpoint = { 6, 7 };

		EXPECT_TRUE(Rect(sdlrect) == Rect(1, 2, 3, 4));
		EXPECT_TRUE(Point(sdlpoint) == Point(6, 7));

		EXPECT_TRUE(Rect(sdlrect) != Rect(0, 2, 3, 4));
		EXPECT_TRUE(Point(sdlpoint) != Point(0, 7));

		EXPECT_TRUE(Rect(1, 2, 3, 4) == sdlrect);
		EXPECT_TRUE(Point(6, 7) == sdlpoint);

		EXPECT_TRUE(Rect(0, 2, 3, 4) != sdlrect);
		EXPECT_TRUE(Point(0, 7) != sdlpoint);
	}

	{
		// clamp
		Rect rect(1, 2, 3, 4);
		EXPECT_EQUAL(Point(0, 0).GetClamped(rect), Point(1, 2));
		EXPECT_EQUAL(Point(0, 0).Clamp(rect), Point(1, 2));

		EXPECT_EQUAL(Point(10, 10).GetClamped(rect), Point(3, 5));
		EXPECT_EQUAL(Point(10, 10).Clamp(rect), Point(3, 5));
	}

	{
		// wrap
		EXPECT_EQUAL(Point(10, 20).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(39, 59).GetWrapped(Rect(10, 20, 30, 40)), Point(39, 59));

		EXPECT_EQUAL(Point(9, 20).GetWrapped(Rect(10, 20, 30, 40)), Point(39, 20));
		EXPECT_EQUAL(Point(40, 20).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(10, 19).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 59));
		EXPECT_EQUAL(Point(10, 60).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));

		EXPECT_EQUAL(Point(-50, -60).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(-20, -20).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(10, 20).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(40, 60).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(70, 100).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));
		EXPECT_EQUAL(Point(100, 140).GetWrapped(Rect(10, 20, 30, 40)), Point(10, 20));

		EXPECT_EQUAL(Point(-19, -19).GetWrapped(Rect(10, 20, 30, 40)), Point(11, 21));
		EXPECT_EQUAL(Point(-21, -21).GetWrapped(Rect(10, 20, 30, 40)), Point(39, 59));
	}

	{
		// streams
		std::stringstream stream;
		stream << Point(1, 2);
		EXPECT_EQUAL(stream.str(), "[x:1,y:2]");
		stream.str("");
		stream << Rect(1, 2, 3, 4);
		EXPECT_EQUAL(stream.str(), "[x:1,y:2,w:3,h:4]");
	}
END_TEST()
