package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Wall extends GameObject{

	private static final String symbol3 = "█";
	
	private static final String symbol2 = "▒";

	private static final String symbol1 = "░";
	
	public static final String INFO = "[WALL] hard obstacle";
	
	private int vida;
	
	
	public Wall(Game game, int x, int y) {
		
		super(game, x, y);
	}


	@Override
	public void receiveCollision(Player player) {
		
		if(vida != 0) {
		
			this.vida = 0;
			player.crash();
		}
		
	}


	@Override
	public boolean isAlive() {
		
		if(vida == 0) return false;
		else return true;
	}


	@Override
	public void onEnter() {
		
		this.vida = 3;
		
	}
	
	public String toString() {
		
		if(vida == 3) return symbol3;
		else if(vida == 2) return symbol2;
		else if(vida == 1) return symbol1;
		else return " ";
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(") ").append(this.vida).append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}


	@Override
	public void update() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onDelete() {
		
		game.moreCoins(5);
	}


	@Override
	public boolean receiveShoot() {
		
		this.vida--;
		return true;
	}


	@Override
	public void receiveExplosion() {
		
		this.receiveShoot();
	}
	
}
