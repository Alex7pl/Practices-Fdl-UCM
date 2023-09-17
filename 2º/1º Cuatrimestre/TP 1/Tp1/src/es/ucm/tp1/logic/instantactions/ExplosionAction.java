package es.ucm.tp1.logic.instantactions;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;


public class ExplosionAction implements InstantAction{
	
	private int x, y;
	
	public ExplosionAction(int x, int y) {
		
		this.x = x;
		this.y = y;
	}
	
	@Override
	public void execute(Game game) {
		
		game.explosion(x, y);
	}
}
