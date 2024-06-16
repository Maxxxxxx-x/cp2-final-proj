all:
	gcc ./src/main.c ./src/utils.c ./src/window.c ./src/save.c ./src/game.c ./src/player.c ./Script/yaml_init.c ./src/inventory.c ./src/scene.c ./src/item.c ./src/character.c ./include/cJSON.c -I ./include/yaml/include/ -L ./include/yaml/lib/ -lyaml -lcurl -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf -o engine

clean:
	rm -f ./engine
