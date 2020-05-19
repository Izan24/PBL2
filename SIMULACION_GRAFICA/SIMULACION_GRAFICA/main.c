#include "sfd.h"


int main() {
	sfd_Options opt = {
		.title = "Mapa kargatu",
		.filter_name = "Mapak",
		.filter = "*.json",
	};

	const char* filename = sfd_open_dialog(&opt);


}



