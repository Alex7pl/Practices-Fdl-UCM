package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.Buyable;
import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.NotEnoughCoinsException;
import es.ucm.tp1.logic.Game;
import es.ucm.tp1.logic.instantactions.ShootAction;

public class ShootCommand extends Command implements Buyable{
	
	private static final String NAME = "shoot";

	private static final String DETAILS = "[s]hoot";

	private static final String SHORTCUT = "s";

	private static final String HELP = "shoot bullet";

	private static final String FAILED_MSG = "Failed to shoot";
	
	
	public ShootCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}


	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		try {
			
			this.buy(game);
			
			game.moreCoins(-this.cost());
		
			game.execute(new ShootAction(game.getPlayerFile(), game.getPlayerCol()));
		
			game.update(game.go(), game.getPlayerCol());
		
		}
		catch(NotEnoughCoinsException e) {
			
			System.out.println(e.getMessage());
			throw new CommandExecuteException(String.format("[ERROR]: %s", FAILED_MSG), e);
		}
		
		return true;
	}


	@Override
	public int cost() {
		// TODO Auto-generated method stub
		return 1;
	}
}
