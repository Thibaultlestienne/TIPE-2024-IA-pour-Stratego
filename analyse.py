import numpy as np
import matplotlib.pyplot as plt


chemin_fichier = 'formation/sortie.txt' #  Nom du fichier
# 5 pour  les test 100 pour de vrai
taille_fenetre_glissante = 100  # Taille de la fenêtre pour la moyenne glissante

def moyenne_glissante(donnees, taille_fenetre_glissante):
    return np.convolve(donnees, np.ones(taille_fenetre_glissante), 'valid') / taille_fenetre_glissante

def extraire_donnees(chemin_fichier):
    generations = []

    with open(chemin_fichier, 'r') as file:
        fichier = file.read()
        donnee_une_generation = fichier.split('GENERATION')[1:]

        for donnee in donnee_une_generation:
            lignes = donnee.strip().split('\n')
            generation_donnees = {}

            for ligne in lignes:
                if 'temps de formation' in ligne:
                    temps = int(ligne.split(':')[-1].strip())
                    generation_donnees['temps_de_formation'] = temps
                elif 'nombre de victoire' in ligne:
                    victoires = int(ligne.split(':')[-1].strip())
                    generation_donnees['nombre_de_victoire'] = victoires
                elif "nombre d'égalité" in ligne:
                    egalites = int(ligne.split(':')[-1].strip())
                    generation_donnees['nombre_d_égalité'] = egalites
                elif 'nombre de coup moyen' in ligne:
                    nombre_de_coups_moyens = int(ligne.split(':')[-1].strip())
                    generation_donnees['nombre_de_coup_moyen'] = nombre_de_coups_moyens
                elif 'nombre de famille differentes' in ligne:
                    familles = int(ligne.split(':')[-1].strip())
                    generation_donnees['nombre_de_famille_differentes'] = familles
            # print(generation_donnees)
            generations.append(generation_donnees)

    return generations

generations_donnees = extraire_donnees(chemin_fichier)

# affichage
# for gen_index, gen_donnees in enumerate(generations_donnees):
#     print(f'Generation {gen_index}:')
#     print(gen_donnees)
#     print()



# Tracer le nombre de victoires par génération
plt.figure(figsize=(10, 6))
plt.plot([gen_donnees['nombre_de_victoire'] for gen_donnees in generations_donnees], marker='o', label='Nombre de victoires')
plt.plot(moyenne_glissante([gen_donnees['nombre_de_victoire'] for gen_donnees in generations_donnees], taille_fenetre_glissante), marker='x', label=f'Moyenne glissante sur {taille_fenetre_glissante} éléments')
plt.xlabel('Génération')
plt.ylabel('Nombre de victoires')
plt.title('Nombre de victoires par génération')
plt.grid()
plt.legend()
plt.savefig('formation/graphiques/nombre_de_victoires.png')

# Tracer le nombre de coups moyen par génération
plt.figure(figsize=(10, 6))
plt.plot([gen_donnees['nombre_de_coup_moyen'] for gen_donnees in generations_donnees], marker='o', label='Nombre de coups moyen')
plt.plot(moyenne_glissante([gen_donnees['nombre_de_coup_moyen'] for gen_donnees in generations_donnees], taille_fenetre_glissante), marker='x', label=f'Moyenne glissante sur {taille_fenetre_glissante} éléments')
plt.xlabel('Génération')
plt.ylabel('Nombre de coups moyen')
plt.title('Nombre de coups moyen par génération')
plt.grid()
plt.legend()
plt.savefig('formation/graphiques/coups_moyen.png')

# Tracer le nombre de familles différentes par génération
plt.figure(figsize=(10, 6))
plt.plot([gen_donnees['nombre_de_famille_differentes'] for gen_donnees in generations_donnees], marker='o', label='Nombre de familles différentes')
plt.plot(moyenne_glissante([gen_donnees['nombre_de_famille_differentes'] for gen_donnees in generations_donnees], taille_fenetre_glissante), marker='x', label=f'Moyenne glissante sur {taille_fenetre_glissante} éléments')
plt.xlabel('Génération')
plt.ylabel('Nombre de familles différentes')
plt.title('Nombre de familles différentes par génération')
plt.grid()
plt.legend()
plt.savefig('formation/graphiques/familles_differentes.png')

# Tracer le temps de formation par génération
plt.figure(figsize=(10, 6))
plt.plot([gen_donnees.get('temps_de_formation', 0) for gen_donnees in generations_donnees], marker='o', label='Temps de formation')
plt.plot(moyenne_glissante([gen_donnees.get('temps_de_formation', 0) for gen_donnees in generations_donnees], taille_fenetre_glissante), marker='x', label=f'Moyenne glissante sur {taille_fenetre_glissante} éléments')
plt.xlabel('Génération')
plt.ylabel('Temps de formation (s)')
plt.title('Temps de formation par génération')
plt.grid()
plt.legend()
plt.savefig('formation/graphiques/temps_par_generation.png')
