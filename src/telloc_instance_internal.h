#ifndef TELLOC_INSTANCE_INTERNAL_H
#define TELLOC_INSTANCE_INTERNAL_H

#include "api/telloc_config_internal.h"

struct TellocInstanceInternal
{
	TellocInstanceInternal(const TellocConfigInternal& config);

	virtual ~TellocInstanceInternal();

protected:
	const TellocConfigInternal config_;
};

#endif
