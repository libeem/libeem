#include <stdio.h>

#include <eem.h>

struct my_obj {
	eem_t eem;
	int a;
};

static void cb(eem_ev_t *ev, void *arg)
{
	struct my_obj *mo = ev->obj;

	printf("New event!\n");
	printf("Event ID: %d\n", ev->ev);
	printf("Data: %p\n", ev->data);
	printf("(char*)Data: %s\n", (char*)ev->data);
	printf("my_obj.a = %d\n", mo->a);
	printf("\n");
}

int main(){

	struct my_obj mo;
	eem_lsn_t *lsn;

	EEM_INIT(&mo);

	mo.a = 77;

	lsn = EEM_ON(&mo, 0, cb, 0);

	printf("Listener %p\n\n", lsn);

	// Emitting the first event
	EEM_EMIT(&mo, 0, "First emit!");

	// Manually deleting the listener
	EEM_DEL_LSN(&mo, lsn);

	// Should not be fired
	EEM_EMIT(&mo, 0, "Second emit!");

	EEM_ONCE(&mo, 1, cb, 0);

	EEM_EMIT(&mo, 1, "Third emit!");
}
