package es.ucm.tp1.logic;

import es.ucm.tp1.control.Level;
import es.ucm.tp1.logic.gameobjects.*;
import es.ucm.tp1.logic.instantactions.ThunderAction;

// TODO add your imports

public class GameObjectGenerator {

	public static void generateGameObjects(Game game, Level level) {

		for (int x = level.getVisibility() / 2; x < level.getLength() - 1; x++) {
			game.tryToAddObject(new Obstacle(game, game.getRandomWidth(), x), level.obstacleFrequency());
			game.tryToAddObject(new Coin(game, game.getRandomWidth(), x), level.coinFrequency());
			game.tryToAddObject(new Wall(game, game.getRandomWidth(), x), level.advObjFreq());
			game.tryToAddObject(new Turbo(game, game.getRandomWidth(), x), level.advObjFreq());
			if(!SuperCoin.hasSuperCoin()) 
				game.tryToAddObject(new SuperCoin(game, game.getRandomWidth(), game.getRandomLane()), level.advObjFreq());
			game.tryToAddObject(new Truck(game, game.getRandomWidth(), x), level.advObjFreq());
			game.tryToAddObject(new Pedestrian(game, game.getRandomWidth(), x), level.advObjFreq());
		}
	}

	public static void reset(Level level) {
		
		Obstacle.reset ();
		Coin.reset ();
	}
	
	public static void forceAdvanceObject(Game game, int id, int x) {
		
		GameObject o = null;
		
		switch (id) {
		
			case 1:
				o = new Wall(game, game.getRandomWidth(), x);
				break;
			case 2:
				o = new Turbo(game, game.getRandomWidth(), x);
				break;
			case 3:
				o = new SuperCoin(game, game.getRandomWidth(), x);
				break;
			case 4:
				o = new Truck(game, game.getRandomWidth(), x);
				break;
			case 5:
				o = new Pedestrian(game, 0, x);
				break;
		}
		
		game.forceAddObject(o);
	}


	public static void generateRuntimeObjects(Game game) {
		
		if (game.getLevel().hasAdvancedObjects()) {
			
			game.execute(new ThunderAction());
		}
	}
}
