max_allowable_depth=1000

print("// Make sure to undef __BASE_LEVEL before use")
print("#ifndef __BASE_LEVEL")
print("\t#if __INCLUDE_LEVEL__ == 0\n\t\t#define __BASE_LEVEL 1")
for i in range(1,max_allowable_depth+1):
	print(f"\t#elif __INCLUDE_LEVEL__ == {i}\n\t\t#define __BASE_LEVEL {i-1}")
print("\t#else\n\t\t#error \"__BASE_LEVEL cases too shallow. Rebuild!\"")
print("\t#endif\n#endif")