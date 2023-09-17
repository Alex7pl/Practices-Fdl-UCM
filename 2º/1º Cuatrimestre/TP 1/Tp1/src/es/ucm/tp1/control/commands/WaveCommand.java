package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.Buyable;
import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.NotEnoughCoinsException;
import es.ucm.tp1.logic.Game;

public class WaveCommand extends Command implements Buyable{
	
	private static final String NAME = "wave";

	private static final String DETAILS = "[w]ave";

	private static final String SHORTCUT = "w";

	private static final String HELP = "do wave";
	
	private static final String FAILED_MSG = "Failed to make a wave";
	
	public WaveCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}



	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		try {
			
			this.buy(game);
		
			game.moreCoins(-this.cost());
			game.wave();
			game.update(game.go(), game.getPlayerCol());
		}
		catch(NotEnoughCoinsException e){
			
			System.out.println(e.getMessage());
			throw new CommandExecuteException(String.format("[ERROR]: %s", FAILED_MSG), e);
		}
		
		return true;
	}



	@Override
	public int cost() {
		
		return 5;
	}
	
	
	
	
	
}
