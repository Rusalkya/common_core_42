import React, { useRef, useState, useEffect } from 'react'
import './drawing-footer.css'

export const DrawingFooter = () => {
  const canvasRef = useRef(null)
  const ctxRef = useRef(null)
  const [isDrawing, setIsDrawing] = useState(false)
  const [isOpen, setIsOpen] = useState(false)
  const [color, setColor] = useState('#000000')
  const [size, setSize] = useState(3)

  const COLORS = [
    '#000000', // noir
    '#FFFFFF', // blanc
    '#8B5CF6', // violet
    '#F97316', // orange
    '#22C55E', // vert
    '#EC4899', // rose
    '#3B82F6', // bleu
    '#FACC15', // jaune
  ]

  // Initialize canvas
  useEffect(() => {
    if (!isOpen || !canvasRef.current) return

    const canvas = canvasRef.current
    canvas.width = window.innerWidth
    canvas.height = window.innerHeight

    const ctx = canvas.getContext('2d')
    ctx.lineCap = 'round'
    ctx.lineJoin = 'round'
    ctx.strokeStyle = color
    ctx.lineWidth = size

    ctxRef.current = ctx
  }, [isOpen])

  // Update color and size
  useEffect(() => {
    if (ctxRef.current) {
      ctxRef.current.strokeStyle = color
      ctxRef.current.lineWidth = size
    }
  }, [color, size])

  const startDrawing = (e) => {
    const { offsetX, offsetY } = e.nativeEvent
    ctxRef.current.beginPath()
    ctxRef.current.moveTo(offsetX, offsetY)
    setIsDrawing(true)
  }

  const draw = (e) => {
    if (!isDrawing) return
    const { offsetX, offsetY } = e.nativeEvent
    ctxRef.current.lineTo(offsetX, offsetY)
    ctxRef.current.stroke()
  }

  const stopDrawing = () => {
    ctxRef.current.closePath()
    setIsDrawing(false)
  }

  const clearCanvas = () => {
    const canvas = canvasRef.current
    ctxRef.current.clearRect(0, 0, canvas.width, canvas.height)
  }

  const saveImage = () => {
    const link = document.createElement('a')
    link.download = 'gribouillis.png'
    link.href = canvasRef.current.toDataURL('image/png')
    link.click()
  }

  const closeDrawing = () => {
    setIsOpen(false)
  }

  if (!isOpen) {
    return (
      <div className="drawing-footer-button">
        <button
          onClick={() => setIsOpen(true)}
          className="btn-gribouiller"
          title="Gribouiller sur la page"
        >
          🎨
        </button>
      </div>
    )
  }

  return (
    <>
      <canvas
        ref={canvasRef}
        className="drawing-canvas-overlay"
        onMouseDown={startDrawing}
        onMouseMove={draw}
        onMouseUp={stopDrawing}
        onMouseLeave={stopDrawing}
      />

      {/* Controls */}
      <div className="drawing-overlay-controls">
        {/* Colors */}
        <div className="colors-palette">
          {COLORS.map((c) => (
            <button
              key={c}
              onClick={() => setColor(c)}
              className={`color-btn ${color === c ? 'active' : ''}`}
              style={{ backgroundColor: c, border: color === c ? '3px solid #333' : '2px solid #999' }}
              title={c}
            />
          ))}
        </div>

        {/* Size slider */}
        <div className="size-control">
          <label>Taille:</label>
          <input
            type="range"
            min="1"
            max="30"
            value={size}
            onChange={(e) => setSize(e.target.value)}
            className="size-slider"
          />
          <span>{size}px</span>
        </div>

        {/* Actions */}
        <div className="action-buttons">
          <button onClick={clearCanvas} className="btn-action btn-clear" title="Effacer">
            🗑️ Effacer
          </button>
          <button onClick={saveImage} className="btn-action btn-save" title="Telecharger">
            💾 Telecharger
          </button>
          <button onClick={closeDrawing} className="btn-action btn-close" title="Fermer">
            ✕ Fermer
          </button>
        </div>
      </div>
    </>
  )
}
