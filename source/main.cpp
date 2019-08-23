#include "Core/Root.hpp"
#include "generator.hpp"

int main ()
{
	KFTG::Root root;
	while (!(root.isQuit ()))
		root.loop ();
	root.~Root ();
	return 0;
}