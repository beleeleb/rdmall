/*
 * wd.h
 *
 *  Created on: Jan 12, 2015
 *      Author: student
 */

#ifndef __WD_H__
#define __WD_H__

typedef struct handle handle_t;

handle_t* create_wd(void);

void destroy_wd(handle_t* handle);

#endif /* __WD_H__ */
