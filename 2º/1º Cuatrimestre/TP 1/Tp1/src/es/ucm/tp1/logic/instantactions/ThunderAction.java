package es.ucm.tp1.logic.instantactions;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.InstantAction;

public class ThunderAction implements InstantAction{
	
	
	
	@Override
	public void execute(Game game) {
		
		game.thunder();
	}
}
