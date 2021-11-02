#ifndef CLASSE_PACOTE_H 
#define CLASSE_PACOTE_H

namespace Package 
{
	class Pacote 
	{
		private:
			unsigned indice;
			float tempo;
			char origem[40];
			char destino[40];
			char protocolo[18];
			unsigned tamanho;
			char informacao[100];

		public:
			Pacote();
			~Pacote();
			void inserir();
	};
}


#endif /* CLASSE_PACOTE_H */