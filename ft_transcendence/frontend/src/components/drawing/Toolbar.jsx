/**
 * @responsable clfouger
 * COMPOSANT TOOLBAR - Barre d'outils de dessin
 */

import { Button } from '../ui/Button'
import brushIcon from '../../assets/logo/canva tools/brush.png'
import eraserIcon from '../../assets/logo/canva tools/eraser.png'
import lineIcon from '../../assets/logo/canva tools/line.png'
import circleIcon from '../../assets/logo/canva tools/circle.png'
import squareIcon from '../../assets/logo/square.png'

export const Toolbar = ({
  tool,
  onToolChange,
  color,
  onColorChange,
  size,
  onSizeChange,
  onUndo,
  onRedo,
  onClear,
  canUndo,
  canRedo,
  opacity,
  onOpacityChange
}) => {
  const tools = [
    { id: 'brush', label: 'Pinceau', icon: brushIcon },
    { id: 'eraser', label: 'Gomme', icon: eraserIcon },
    { id: 'line', label: 'Ligne', icon: lineIcon },
    { id: 'circle', label: 'Cercle', icon: circleIcon },
    { id: 'rect', label: 'Carre', icon: squareIcon },
  ]

  const colors = ['#000000', '#FF0000', '#00FF00', '#0000FF', '#FFFF00', '#FF00FF', '#00FFFF', '#FFFFFF']

  return (
    <div className="toolbar">
      {/* Outils */}
      <div className="toolbar-group">
        <span className="toolbar-label">OUTILS</span>
        {tools.map(t => (
          <button
            key={t.id}
            className={`tool-button ${tool === t.id ? 'active' : ''}`}
            onClick={() => onToolChange(t.id)}
            title={t.label}
            style={{
              display: 'flex',
              alignItems: 'center',
              justifyContent: 'center',
              width: '32px',
              height: '32px',
            }}
          >
            <img src={t.icon} alt={t.label} style={{ width: '24px', height: '24px', objectFit: 'contain' }} />
          </button>
        ))}
      </div>

      {/* Couleur */}
      <div className="toolbar-group">
        <span className="toolbar-label">COULEUR</span>
        <div className="color-picker-wrapper">
          <input
            type="color"
            value={color}
            onChange={(e) => onColorChange(e.target.value)}
            className="color-input"
            title="Selectionner une couleur"
          />
          <div className="color-presets">
            {colors.map(c => (
              <button
                key={c}
                className={`color-preset ${color === c ? 'active' : ''}`}
                style={{ backgroundColor: c }}
                onClick={() => onColorChange(c)}
                title={`Couleur ${c}`}
              />
            ))}
          </div>
        </div>
      </div>

      {/* Taille et opacite */}
      <div className="toolbar-group">
        <span className="toolbar-label">PINCEAU</span>
        <div className="brush-settings">
          <label style={{ fontSize: 'var(--font-size-xs)' }}>
            Taille:
            <input
              type="range"
              min="1"
              max="50"
              value={size}
              onChange={(e) => onSizeChange(Number(e.target.value))}
              className="size-slider"
              style={{ marginLeft: 'var(--spacing-sm)' }}
            />
            <span className="size-value">{size}px</span>
          </label>
        </div>
        <div className="brush-settings">
          <label style={{ fontSize: 'var(--font-size-xs)' }}>
            Opacite:
            <input
              type="range"
              min="0"
              max="1"
              step="0.1"
              value={opacity}
              onChange={(e) => onOpacityChange(Number(e.target.value))}
              className="size-slider"
              style={{ marginLeft: 'var(--spacing-sm)' }}
            />
            <span className="size-value">{Math.round(opacity * 100)}%</span>
          </label>
        </div>
      </div>

      {/* Actions */}
      <div className="toolbar-group">
        <span className="toolbar-label">ACTIONS</span>
        <button
          className={`tool-button ${!canUndo ? 'disabled' : ''}`}
          onClick={onUndo}
          disabled={!canUndo}
          title="Annuler"
        >
          ↶
        </button>
        <button
          className={`tool-button ${!canRedo ? 'disabled' : ''}`}
          onClick={onRedo}
          disabled={!canRedo}
          title="Retablir"
        >
          ↷
        </button>
        <button
          className="tool-button"
          onClick={onClear}
          title="Effacer le canvas"
        >
          🗑️
        </button>
      </div>
    </div>
  )
}
