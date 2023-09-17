package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Coin extends GameObject{
	
	private static final String symbol = "¢";

	public static final String INFO = "[Coin] gives 1 coin to the player";
	
	private boolean vida;

	private static int coinsCount;
	
	
	
	public Coin(Game game, int x, int y) {
		
		super(game, x, y);
	}

	public String toString() {
		
		return symbol;
	}
	
	public static void reset() {
		
		coinsCount = 0;
	}
	
	public static int getCoinsCount() {
		
		return coinsCount;
	}

	@Override
	public void receiveCollision(Player player) {
		
		this.vida = false;
		player.moreCoins(1);
		
	}


	@Override
	public boolean isAlive() {
		
		return this.vida;
	}


	@Override
	public void onEnter() {

		coinsCount = coinsCount + 1;
		this.vida = true;
		
	}

	@Override
	public void update() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public void onDelete() {
		
		coinsCount = coinsCount - 1;
		
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

	@Override
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(")").append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}
	
	
}
