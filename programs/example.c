#include <stdio.h>

#include <eem.h>

struct ms {
	eem_t eem;
	int a;
};

static void cb(eem_ev_t ev, void *arg)
{
	printf("LOL\n");
}

int main(){

	struct ms ms;
	eem_lsn_t *lsn;

	EEM_INIT(&ms.eem);

	lsn = EEM_ON(&ms.eem, 0, cb, 0);

	printf("Listener %p\n", lsn);

	EEM_EMIT(&ms.eem, 0, 0);
	EEM_EMIT(&ms.eem, 0, 0);


}
