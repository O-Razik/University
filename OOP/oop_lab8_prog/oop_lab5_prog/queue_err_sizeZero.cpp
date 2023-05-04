#include "queue_err_sizeZero.h"

char const* queue_err_sizeZero::what() const
{
	return "Queue's size cannot be zero\n";
}