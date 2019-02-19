#pragma once

#if defined (DEBUG) || defined (_DEBUG)

#define new new(__FILE__, __FUNCTION__, __LINE__)
#define delete delete

#endif