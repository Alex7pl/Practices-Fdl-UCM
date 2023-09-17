package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Turbo extends GameObject{
	
	private static final String symbol = ">>>";
	
	public static final String INFO = "[TURBO] pushes the car 3 columns";
	
	private boolean vida;
	
	public Turbo(Game game, int x, int y) {
		
		super(game, x, y);
	}

	@Override
	public void receiveCollision(Player player) {
		
		this.vida = false;
		player.update(player.getX(), player.getY() + 3);
	}

	@Override
	public boolean isAlive() {
		
		return vida;
	}

	@Override
	public void onEnter() {
		
		this.vida = true;
	}
	
	public String toString() {
		
		return Turbo.symbol;
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(")").append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}
	
	@Override
	public void update() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onDelete() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean receiveShoot() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void receiveExplosion() {
		// TODO Auto-generated method stub
		
	}
	
	
}
