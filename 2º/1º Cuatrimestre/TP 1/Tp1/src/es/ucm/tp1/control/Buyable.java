package es.ucm.tp1.control;

import es.ucm.tp1.control.exceptions.NotEnoughCoinsException;
import es.ucm.tp1.logic.Game;

public interface Buyable {
	
	public int cost();
	
	public default void buy(Game game) throws NotEnoughCoinsException{
	
		if(game.playerCoins() < this.cost()) throw new NotEnoughCoinsException("Not enough coins");
	};

}
