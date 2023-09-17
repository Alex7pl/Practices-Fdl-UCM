package es.ucm.tp1.control.commands;

import es.ucm.tp1.control.exceptions.CommandExecuteException;
import es.ucm.tp1.control.exceptions.CommandParseException;
import es.ucm.tp1.logic.Game;

public class UpdateCommand extends Command {

	private static final String NAME = "update";

	private static final String DETAILS = "[n]one | []";

	private static final String SHORTCUT = "n";

	private static final String HELP = "update";

	public UpdateCommand() {
		super(NAME, SHORTCUT, DETAILS, HELP);
	}

	@Override
	public boolean execute(Game game) throws CommandExecuteException{
		
		game.update(game.go(), game.getPlayerCol() + 1);
		
		return true;
	}

	@Override
	protected Command parse(String[] words) throws CommandParseException {
		if ("".equalsIgnoreCase(words[0])) {
			words[0] = SHORTCUT;
		}
		if (matchCommandName(words[0])) {
			
			if (words.length != 1) {
				throw new CommandParseException(String.format("[ERROR]: Command %s: %s", NAME, INCORRECT_NUMBER_OF_ARGS_MSG));
			} else {
				return this;
			}
		}
		
		return null;
	}
}
