#ifndef _COLOR_H_
#define _COLOR_H_


class Color4
{
public:
	union
	{
		struct
		{
			unsigned char r,g,b,a;
		};
		unsigned char v[4];
	};
};

#endif