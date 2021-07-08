#ifndef __LOGGER_H__
#define __LOGGER_H__

typedef struct Logger Logger;

/* ../src/logger.c */
extern Logger *logger_create(void);
extern _Bool logger_start(Logger *l);
extern _Bool logger_end(Logger *l);

#endif /* ifndef __LOGGER_H__ */
