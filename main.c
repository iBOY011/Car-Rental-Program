#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100
#define MAX_VOITURES 100

struct Client {
    char nom[20];
    char prenom[20];
    char date_naissance[11];
};

struct Voiture {
    char marque[20];
    char type[20];
    char immatriculation[20];
    char couleur[20];
};

void ajouter_client();
void ajouter_voiture();
void creer_reservation();
void afficher_reservations();
void afficher_voitures();

int main() {
    int choix;

    printf("=== Gestion de location de voitures ===\n");
    while (1) {
        printf("\nMenu :\n");
        printf("1. Ajouter un client\n");
        printf("2. Ajouter une voiture\n");
        printf("3. Créer une réservation\n");
        printf("4. Afficher les réservations\n");
        printf("5. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        switch (choix) {
            case 1:
                ajouter_client();
                break;
            case 2:
                ajouter_voiture();
                break;
            case 3:
                creer_reservation();
                break;
            case 4:
                afficher_reservations();
                break;
            case 5:
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }

    return 0;
}

void ajouter_client() {
    FILE *fichier_client = fopen("fichier_client.txt", "a");
    if (fichier_client == NULL) {
        fprintf(stderr, "\nErreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    struct Client nouveau_client;

    printf("Nom du client : ");
    fgets(nouveau_client.nom, sizeof(nouveau_client.nom), stdin);
    strtok(nouveau_client.nom, "\n");

    printf("Prénom du client : ");
    fgets(nouveau_client.prenom, sizeof(nouveau_client.prenom), stdin);
    strtok(nouveau_client.prenom, "\n");

    printf("Date de naissance du client (jj/mm/aaaa) : ");
    fgets(nouveau_client.date_naissance, sizeof(nouveau_client.date_naissance), stdin);
    strtok(nouveau_client.date_naissance, "\n");

    fprintf(fichier_client, "%s %s %s\n", nouveau_client.nom, nouveau_client.prenom, nouveau_client.date_naissance);

    fclose(fichier_client);

    printf("Le client a été ajouté avec succès.\n");
}

void ajouter_voiture() {
    FILE *fichier_voiture = fopen("fichier_voiture.txt", "a");
    if (fichier_voiture == NULL) {
        fprintf(stderr, "\nErreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    struct Voiture nouvelle_voiture;

    printf("Marque de la voiture : ");
    fgets(nouvelle_voiture.marque, sizeof(nouvelle_voiture.marque), stdin);
    strtok(nouvelle_voiture.marque, "\n");

    printf("Type de la voiture : ");
    fgets(nouvelle_voiture.type, sizeof(nouvelle_voiture.type), stdin);
    strtok(nouvelle_voiture.type, "\n");

    printf("Immatriculation de la voiture : ");
    fgets(nouvelle_voiture.immatriculation, sizeof(nouvelle_voiture.immatriculation), stdin);
    strtok(nouvelle_voiture.immatriculation, "\n");

    printf("Couleur de la voiture : ");
    fgets(nouvelle_voiture.couleur, sizeof(nouvelle_voiture.couleur), stdin);
    strtok(nouvelle_voiture.couleur, "\n");

    fprintf(fichier_voiture, "%s %s %s %s\n", nouvelle_voiture.marque, nouvelle_voiture.type, nouvelle_voiture.immatriculation, nouvelle_voiture.couleur);

    fclose(fichier_voiture);

    printf("La voiture a été ajoutée avec succès.\n");
}

void creer_reservation() {
    printf("\nVoitures disponibles :\n");
    afficher_voitures();

    FILE *fichier_reservation = fopen("fichier_reservation.txt", "a");
    if (fichier_reservation == NULL) {
        fprintf(stderr, "\nErreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char nom_client[20], marque_voiture[20];
    int jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin;

    printf("\nNom du client : ");
    fgets(nom_client, sizeof(nom_client), stdin);
    strtok(nom_client, "\n");

    printf("Marque de la voiture : ");
    fgets(marque_voiture, sizeof(marque_voiture), stdin);
    strtok(marque_voiture, "\n");

    printf("Date de début de la réservation (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &jour_debut, &mois_debut, &annee_debut);

    printf("Date de fin de la réservation (jj/mm/aaaa) : ");
    scanf("%d/%d/%d", &jour_fin, &mois_fin, &annee_fin);

    fprintf(fichier_reservation, "%s %s %02d/%02d/%04d %02d/%02d/%04d\n", nom_client, marque_voiture, jour_debut, mois_debut, annee_debut, jour_fin, mois_fin, annee_fin);

    fclose(fichier_reservation);

    printf("\nLa réservation a été créée avec succès.\n");
}

void afficher_reservations() {
    FILE *fichier_reservation = fopen("fichier_reservation.txt", "r");
    if (fichier_reservation == NULL) {
        fprintf(stderr, "\nErreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    printf("\nListe des réservations :\n");

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fichier_reservation) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier_reservation);
}

void afficher_voitures() {
    FILE *fichier_voiture = fopen("fichier_voiture.txt", "r");
    if (fichier_voiture == NULL) {
        fprintf(stderr, "\nErreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), fichier_voiture) != NULL) {
        printf("%s", ligne);
    }

    fclose(fichier_voiture);
}