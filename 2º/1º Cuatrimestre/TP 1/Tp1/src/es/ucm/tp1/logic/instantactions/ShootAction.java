package es.ucm.tp1.logic.instantactions;

import es.ucm.tp1.logic.InstantAction;

import es.ucm.tp1.logic.Game;

public class ShootAction implements InstantAction{

	
	private int x, y;
	
	public ShootAction(int x, int y) {
		
		this.x = x;
		this.y = y;
	}
	
	@Override
	public void execute(Game game) {
		
		game.shoot(x, y);
	}

}
