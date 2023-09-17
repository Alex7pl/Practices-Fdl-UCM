package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class SuperCoin extends GameObject{
	
	private static final String symbol = "$";
	
	public static final String INFO = "[SUPERCOIN] gives 1000 coins";
	
	private static boolean vida;
	
	public SuperCoin(Game game, int x, int y) {
		
		super(game, x, y);
	}

	@Override
	public void receiveCollision(Player player) {
		
		SuperCoin.vida = false;
		
		player.moreCoins(1000);
	}

	@Override
	public boolean isAlive() {
		
		return vida;
	}
	
	public static boolean hasSuperCoin() {
		
		if(SuperCoin.vida == true) return true;
		else return false;
		
	}

	@Override
	public void onEnter() {
		
		SuperCoin.vida = true;
	}
	
	public String toString() {
		
		return SuperCoin.symbol;
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
		SuperCoin.vida = false;
		
	}

	@Override
	public boolean receiveShoot() {
		// TODO Auto-generated method stub
		return false;	}

	@Override
	public void receiveExplosion() {
		// TODO Auto-generated method stub
		
	}
	
	
}
