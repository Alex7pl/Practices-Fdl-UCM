package es.ucm.tp1.view;

import es.ucm.tp1.logic.Game;
import es.ucm.tp1.utils.StringUtils;

public class GameSerializer {
	
	private static final String COINS_MSG = "Coins: ";

	private static final String CYCLE_MSG = "Cycle: ";
	
	private static final String ELAPSED_TIME_MSG = "Elapsed Time: ";
	
	private static final String INTRO = "---- ROAD FIGHTER SERIALIZED ---- \n";
	
	private static final String LEVEL_MSG = "Level: ";
	
	private static String formatTime(long t) {
		return String.format("%.2f s", t / 1000.0);
	}
	
	private Game game;
	
	
	public GameSerializer(Game game) {
		
		this.game = game;
	}
	
	private String getInfo() {
		StringBuilder buffer = new StringBuilder(INTRO);
		/* @formatter:off */
		buffer
		.append(LEVEL_MSG).append(game.getLevelName()).append(StringUtils.LINE_SEPARATOR)
		.append(CYCLE_MSG).append(game.getCycle()).append(StringUtils.LINE_SEPARATOR)
		.append(COINS_MSG).append(game.playerCoins()).append(StringUtils.LINE_SEPARATOR);

		if (!game.isTestMode()) {
			
			buffer
			.append(ELAPSED_TIME_MSG).append(formatTime(game.elapsed()));
			
		}

		return buffer.toString();
	}
	
	public String toString() {
		StringBuilder str = new StringBuilder(getInfo());

		str.append("\nGame Objects: \n");

		for (int x = 0; x < game.getLevelLength() - 1; x++) {
			for (int y = 0; y < game.getRoadWidth(); y++) {
				
				str.append(game.serialize(y, x));
				
			}
		}

		return str.toString();
	}
}
