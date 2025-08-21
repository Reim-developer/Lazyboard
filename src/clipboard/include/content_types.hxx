#ifndef CONTENT_TYPES_HXX
#define CONTENT_TYPES_HXX

#include <cstdint>
using std::uint8_t;
namespace Lazyboard::clipboard {
enum class ContentTypes : uint8_t {
	TEXT,
	HTML,
	URL,
	PATH,
	IMAGE,
};
}

#endif