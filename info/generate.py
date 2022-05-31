import glob, re, os


os.chdir("info/generated")

# Fix for dia lower than 1.0 generating .h and not .hpp
h_headers = glob.glob("*.h")
if h_headers != []:
	for header in h_headers:
		os.rename(header, header + "pp")

if glob.glob("array.hpp"):
	os.remove("array.hpp")


################################# TOOLS ############################################################ 

def adds_line_after_tag(filename, tag, new_line):
	with open(filename, "r") as read_file, open(filename + ".tmp", "w") as output_file:
		for line in read_file:
			output_file.write(line)
			if re.match(tag, line):
				output_file.write(new_line + "\n")
	os.rename(filename + ".tmp", filename)

def replace_line(filename, tag_line, new_line):
	with open(filename, "r") as read_file, open(filename + ".tmp", "w") as output_file:
		for line in read_file:
			if tag_line in line:
				output_file.write(new_line + "\n")
			else :
				output_file.write(line)
			
	os.rename(filename + ".tmp", filename)

def adds_base_types(filename):
	adds_line_after_tag(filename, "^#define.*__HPP$", '\n#include "type.h"')


################################# END TOOLS ######################################################## 


if __name__ == "__main__":
	# To have all header use the same type
	for filename in glob.glob("*.hpp"):
		adds_base_types(filename)

	# The AnimationAtlas has to include the c data
	adds_line_after_tag("AnimationAtlas.hpp", '^#include "type.h"$', '#include "animation_resource.h"')
	#TODO maybe remove this (the pointer can be found with an hard adress)
	adds_line_after_tag("AtlasManager.hpp", '^#include "type.h"$', '#include "animation_resource.h"')

	adds_line_after_tag("ObjectManager.hpp", '^#include "type.h"$', '#include "object.h"')
	adds_line_after_tag("Sprite.hpp", '^#include "type.h"$', '#include "object.h"')
	
	adds_line_after_tag("VideoMemoryManager.hpp", '^#include "type.h"$', '#include <list>')

	# replace the generated array with my implementation
	replace_line("AnimationAtlas.hpp", '#include "array.hpp"', '#include "array.h"')

	adds_line_after_tag("AtlasManager.hpp", '#include "type.h"', '#include <list>')
