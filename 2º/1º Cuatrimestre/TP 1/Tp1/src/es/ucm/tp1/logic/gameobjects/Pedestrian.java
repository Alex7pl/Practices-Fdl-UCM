package es.ucm.tp1.logic.gameobjects;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class Pedestrian extends GameObject{
	
	private static final String symbol = "☺";

	public static final String INFO = "[PEDESTRIAN] person crossing the road up and down";
	
	private boolean vida;
	
	private int position;
	
	
	public Pedestrian(Game game, int x, int y) {
		
		super(game, x, y);
	}
	
	
	public String toString() {
		
		return symbol;
	}
	
	public String serialize() {
		StringBuilder str = new StringBuilder();
		
		str.append(this.toString()).append(" (").append(y).append(", ").append(x).append(") ");
		
		if(position < super.x) {
			
			str.append("up");
		}
		else {
			
			str.append("down");
		}
		
		str.append(StringUtils.LINE_SEPARATOR);
		
		return str.toString();
	}

	@Override
	public void receiveCollision(Player player) {
		
		if(vida) {
		
			int coins = 0 - player.playerCoins();
		
			this.vida = false;
			player.crash();
			player.moreCoins(coins);
		}
	}


	@Override
	public boolean isAlive() {
		
		return vida;
	}


	@Override
	public void onEnter() {
		
		vida = true;
		position = super.x;
	}


	@Override
	public void update() {
		
		if(super.x == 0) {
			super.x++;
			position = super.x - 1;
		}
		else if(super.x == super.game.getRoadWidth() - 1) {
			super.x--;
			position = super.x + 1;
		}
		else if(position == super.x) {
			super.x++;
			position = super.x - 1;
		}
		else if(position < super.x) {
			super.x++;
			position = super.x - 1;
		}
		else if(position > super.x) {
			super.x--;
			position = super.x + 1;
		}
	}


	@Override
	public void onDelete() {
		// TODO Auto-generated method stub
		
	}


	@Override
	public boolean receiveShoot() {
		
		this.vida = false;
		int coins = 0 - game.playerCoins();
		game.moreCoins(coins);
		return true;
	}


	@Override
	public void receiveExplosion() {
		
		this.receiveShoot();
	}
	
}
