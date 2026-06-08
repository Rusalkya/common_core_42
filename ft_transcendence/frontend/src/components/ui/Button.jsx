/**
 * @responsable clfouger
 * COMPOSANT BUTTON - Bouton reutilisable
 * 
 * Utilise les classes CSS du design-system
 * Variantes: primary, secondary, danger
 * Tailles: small, medium, large
 */

export const Button = ({
  children,
  variant = 'primary',
  size = 'medium',
  disabled = false,
  onClick,
  className = '',
  ...props
}) => {
  const variantClass = `btn-${variant}`
  const sizeClass = `btn-${size}`

  return (
    <button
      className={`btn ${variantClass} ${sizeClass} ${className}`}
      disabled={disabled}
      onClick={onClick}
      {...props}
    >
      {children}
    </button>
  )
}
