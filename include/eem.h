#ifndef EEM_H
#define EEM_H

#include <string.h>
#include <stdlib.h>

typedef struct eem_ev eem_ev_t;
typedef struct eem_lsn eem_lsn_t;
typedef struct eem eem_t;

typedef void (*eem_lsn_cb)(eem_ev_t *ev, void *arg);

enum eem_lsn_flag {
	EEM_LSN_FLAG_ONCE = 1 << 0
};

struct eem_ev {
	void *obj;
	int ev;
	void *data;
};

struct eem_lsn {
	int sub_ev; // Event to be subscribed
	int flags;
	eem_lsn_cb cb;
	void *arg;
	struct eem_lsn *next;
};

struct eem {
	struct eem_lsn *lsn;
};


#define EEM_LSN_INIT(_lsn, _sub_ev, _flags, _cb, _arg)				\
	({									\
		memset(_lsn, 0, sizeof(eem_lsn_t));				\
		_lsn->sub_ev = _sub_ev;						\
		_lsn->flags = _flags;						\
		(_lsn)->cb = _cb;						\
		_lsn->arg = _arg;						\
	})

#define EEM_INIT(obj)								\
	({									\
		memset(&(obj)->eem, 0, sizeof(eem_t));				\
	})


#define EEM_ADD_LSN(obj, _ev, _flags, _cb, _arg)				\
	({									\
		eem_lsn_t *lsn;							\
										\
		lsn = malloc(sizeof(eem_lsn_t));				\
										\
		EEM_LSN_INIT(lsn, _ev, _flags, _cb, _arg);			\
										\
		lsn->next = (obj)->eem.lsn;					\
		(obj)->eem.lsn = lsn;						\
		lsn;								\
	})

#define EEM_DEL_LSN(obj, _lsn)							\
	 ({									\
		eem_lsn_t *cur, *prev;						\
										\
		prev = 0;							\
		cur = (obj)->eem.lsn;						\
										\
		while (cur) {							\
			if (cur == _lsn) {					\
				if (prev) prev->next = cur->next;		\
				else (obj)->eem.lsn = cur->next;		\
										\
				free(cur);					\
				break;						\
			}							\
			prev = cur;						\
			cur = cur->next;					\
		}								\
										\
	})

#define EEM_ON(obj, ev, cb, arg)						\
	({EEM_ADD_LSN(obj, ev, 0, cb, arg);})

#define EEM_ONCE(obj, ev, cb, arg) 						\
	({EEM_ADD_LSN(obj, ev, EEM_LSN_FLAG_ONCE, cb, arg);})


#define EEM_EMIT(_obj, _ev, _data)						\
	({									\
		eem_ev_t event;							\
		eem_lsn_t *cur, *tmp;						\
										\
		cur = (_obj)->eem.lsn;						\
										\
		while (cur) {							\
			tmp = cur->next;					\
										\
			if (cur->sub_ev == _ev) {				\
				event.obj = _obj;				\
				event.ev = _ev;					\
				event.data = _data;				\
										\
				cur->cb(&event, cur->arg);			\
										\
				if (cur->flags & EEM_LSN_FLAG_ONCE) {		\
					EEM_DEL_LSN(_obj, cur);			\
				}						\
			}							\
										\
			cur = tmp;						\
		}								\
										\
	})



#endif
