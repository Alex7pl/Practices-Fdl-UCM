package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Truck extends GameObject{

	private static final String symbol = "←";

	public static final String INFO = "[TRUCK] moves towards the player";
	
	private boolean vida;
	
	
	public Truck(Game game, int x, int y) {
		
		super(game, x, y);
	}
	
	public String toString() {
		
		return symbol;
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(")").append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}

	@Override
	public void receiveCollision(Player player) {
		
		if(vida) {
		
			this.vida = false;
			player.crash();
		}
	}

	@Override
	public boolean isAlive() {
		
		return vida;
	}

	@Override
	public void onEnter() {
		
		this.vida = true;
		
	}

	@Override
	public void update() {
		
		super.y = super.y - 1;
	}

	@Override
	public void onDelete() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean receiveShoot() {
		
		this.vida = false;
		return true;
	}

	@Override
	public void receiveExplosion() {
		
		this.receiveShoot();
	}
	
	
	

	
}
