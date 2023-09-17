package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.instantactions.ExplosionAction;
import es.ucm.tp1.utils.StringUtils;

public class Grenade extends GameObject{
	
	private static final String symbol = "ð[";
	
	public static final String INFO = "[GRENADE] Explodes in 3 cycles, harming everyone aroun";
	
	private int timer;
	
	
	public Grenade(Game game, int x, int y) {
		
		super(game, x, y);
	}
	
	public String toString() {
		
		return symbol + timer + "]";
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(") ").append(timer).append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}


	@Override
	public void receiveCollision(Player player) {
		// TODO Auto-generated method stub
		
	}


	@Override
	public boolean receiveShoot() {
		// TODO Auto-generated method stub
		return false;
	}


	@Override
	public boolean isAlive() {
		
		if(timer == 0) return false;
		else return true;
	}


	@Override
	public void onEnter() {
		
		this.timer = 4;
	}


	@Override
	public void update() {
		
		timer--;
	}


	@Override
	public void onDelete() {
		
		game.execute(new ExplosionAction(this.x, this.y));
	}

	@Override
	public void receiveExplosion() {
		// TODO Auto-generated method stub
		
	}
	
	
}
