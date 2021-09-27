/**
 * Returns the current memory usage of the running server in kilobytes.
 *
 * @return int - Current memory usage in kilobytes.
 */
native int GetMem();

/**
 * Do not edit below this line!
 */
public Extension __ext_GetMem = 
{
    name = "GetMem",
    file = "sm-getmem.ext",
#if defined AUTOLOAD_EXTENSIONS
    autoload = 1,
#else
    autoload = 0,
#endif
#if defined REQUIRE_EXTENSIONS
    required = 1,
#else
    required = 0,
#endif
};
