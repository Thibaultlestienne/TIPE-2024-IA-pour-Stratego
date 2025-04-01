former :
	# compilation
	gcc ia.c fichier.c stratego.c aleatoire.c tableau_dyn.c affichage.c evaluation.c parcours.c -o ia
	# effacer la formation precedente
	rm -f formation/*/* formation/sortie.txt formation/tableau.csv
	# lancer la formation !! la sortie est redirigée dans formation/sortie.txt !! 
	# !!! Les parametres prérempli permettent une formation en quelques minutes pour tester. !!!
	# !!! Une véritable formation peut prendre de plusieurs heures à plusieurs jours !!!
	./ia > formation/sortie.txt
	# compiler  les fichier pour analyser la formation
	gcc -g comparer_historique_ia.c parcours.c tableau_dyn.c aleatoire.c stratego.c affichage.c fichier.c evaluation.c -o comparer_historique
	# generer les graphiques et le csv
	/bin/python3 analyse.py; ./comparer_historique

compiler_ia_avec_verification_memoire:
	gcc -g ia.c fichier.c stratego.c aleatoire.c tableau_dyn.c affichage.c evaluation.c parcours.c -o ia -fsanitize=address -g

# Permet de add commit et push avec un message par default
partager : 
	rm -f ia
	sh partager.sh		


