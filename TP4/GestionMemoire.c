#include "./libs/lib.h"
#include "stdio.h"
#define TAILLE_PAGE 1024

unsigned int calculerNumeroDePage(unsigned long adresse)
{
	return adresse / TAILLE_PAGE;
}

unsigned long calculerDeplacementDansLaPage(unsigned long adresse)
{
	return adresse % TAILLE_PAGE;
}

unsigned long calculerAdresseComplete(unsigned int numeroDePage, unsigned long deplacementDansLaPage)
{
	return numeroDePage * TAILLE_PAGE + deplacementDansLaPage;
}

void rechercherTLB(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	for (unsigned int i = 0; i < TAILLE_TLB; i++)
	{
		if (mem->tlb->numeroPage[i] == calculerNumeroDePage(req->adresseVirtuelle) && mem->tlb->entreeValide[i])
		{
			req->adressePhysique = calculerAdresseComplete(mem->tlb->numeroCadre[i], calculerDeplacementDansLaPage(req->adresseVirtuelle));
			req->estDansTLB = 1;
			mem->tlb->dernierAcces[i] = req->date;
			return;
		}
	}
	req->adressePhysique = 0;
}

void rechercherTableDesPages(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	unsigned int numeroCadreReq = calculerNumeroDePage(req->adresseVirtuelle);
	if (mem->tp->entreeValide[numeroCadreReq])
	{
		req->adressePhysique = calculerAdresseComplete(mem->tp->numeroCadre[numeroCadreReq], calculerDeplacementDansLaPage(req->adresseVirtuelle));
		req->estDansTablePages = 1;
		return;
	}
	req->adressePhysique = 0;
}

void ajouterDansMemoire(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	for (unsigned int i = 0; i < TAILLE_MEMOIRE; i++)
	{
		if (mem->memoire->utilisee[i] == 0)
		{
			unsigned long adressePhysique = calculerAdresseComplete(i, calculerDeplacementDansLaPage(req->adresseVirtuelle));
			mem->memoire->numeroPage[i] = adressePhysique;
			req->adressePhysique = adressePhysique;
			mem->memoire->dernierAcces[i] = req->date;
			mem->memoire->dateCreation[i] = req->date;
			mem->memoire->utilisee[i] = 1;
			return;
		}
	}
}

void mettreAJourTLB(struct RequeteMemoire *req, struct SystemeMemoire *mem)
{
	unsigned int indiceTLB = 0;
	unsigned long temps = __LONG_MAX__;
	int isFull = 1;
	unsigned long numPageReq = calculerNumeroDePage(req->adresseVirtuelle);
	for (unsigned int i = 0; i < TAILLE_TLB; i++)
	{
		if (mem->tlb->dateCreation[i] < temps)
		{
			temps = mem->tlb->dateCreation[i];
			indiceTLB = i;
		}
		if (!mem->tlb->entreeValide[i])
		{
			isFull = 0;
			break;
		}
	}
	if (!isFull)
	{
		temps = __LONG_MAX__;
		for (unsigned int i = 0; i < TAILLE_TLB; i++)
		{
			if (mem->tlb->dateCreation[i] < temps && !mem->tlb->entreeValide[i])
			{
				temps = mem->tlb->dateCreation[i];
				indiceTLB = i;
			}
		}
		mem->tlb->numeroPage[indiceTLB] = numPageReq;
		mem->tlb->numeroCadre[indiceTLB] = calculerNumeroDePage(req->adressePhysique);
		mem->tlb->entreeValide[indiceTLB] = 1;
		mem->tlb->dernierAcces[indiceTLB] = req->date;
		mem->tlb->dateCreation[indiceTLB] = req->date;
		return;
	}
	for (unsigned int i = 0; i < TAILLE_TLB; i++)
	{
		if (mem->tlb->dateCreation[i] < temps)
		{
			temps = mem->tlb->dateCreation[i];
			indiceTLB = i;
		}
	}
	mem->tlb->numeroPage[indiceTLB] = numPageReq;
	mem->tlb->numeroCadre[indiceTLB] = calculerNumeroDePage(req->adressePhysique);
	mem->tlb->entreeValide[indiceTLB] = 1;
	mem->tlb->dernierAcces[indiceTLB] = req->date;
	mem->tlb->dateCreation[indiceTLB] = req->date;
}

// NE PAS MODIFIER
int main()
{
	evaluate(
		&calculerNumeroDePage,
		&calculerDeplacementDansLaPage,
		&calculerAdresseComplete,
		&rechercherTLB,
		&rechercherTableDesPages,
		&mettreAJourTLB,
		&ajouterDansMemoire);
	return 0;
}
